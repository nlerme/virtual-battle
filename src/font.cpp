#include <vector>
#include <string>
#include <GL/glew.h>
#include "utils.h"
#include "tokenizer.h"
#include "font.h"


CFont::CFont( const std::string & filename, const uint height, const color4f & color ) : m_Textures(NULL), 
											 m_IsLoaded(false)
{
	load(filename, height, color);
}

CFont::~CFont()
{
	if( m_IsLoaded )
	{
		glDeleteLists(m_ListBase, 128);
		glDeleteTextures(128, m_Textures);
		delete [] m_Textures;
	}
}

bool CFont::load( const std::string & filename, const uint height, const color4f & color )
{
	m_Textures = new GLuint[128];
	m_Height   = float(height);

	FT_Library library;
	FT_Face face;

	FT_Init_FreeType(&library);
	FT_New_Face(library, filename.c_str(), 0, &face);
	FT_Set_Char_Size(face, height << 6, height << 6, 96, 96);
 
	m_ListBase = glGenLists(128);
	glGenTextures(128, m_Textures);

	for( uchar i(0); i<128; i++ )
		_build_display_list(face, i);

	FT_Done_Face(face);
	FT_Done_FreeType(library);

	return (m_IsLoaded = true);
}

bool CFont::is_loaded() const
{
	return m_IsLoaded;
}

void CFont::put_text( const std::string & str, const float x, const float y, const color4f & color ) const
{
	glColor4f(color.r, color.g, color.b, color.a);

	_push_matrix();

	uint font(m_ListBase);
	float height(m_Height / 0.63f);

	std::vector<std::string> lines(CNewLineTokenizer::tokenize(str));

	glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT | GL_ENABLE_BIT | GL_TRANSFORM_BIT);
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glListBase(font);

	float model_view_matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, model_view_matrix);

	for( uint i(0); i<lines.size(); i++ )
	{
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(x, y - height * i, 0);
		glMultMatrixf(model_view_matrix);
		glCallLists(lines[i].length(), GL_UNSIGNED_BYTE, lines[i].c_str());
		glPopMatrix();
	}

	glPopAttrib();

	_pop_matrix();

	glDisable(GL_TEXTURE_2D);
}

void CFont::_build_display_list( FT_Face face, char character )
{
	FT_Load_Glyph(face, FT_Get_Char_Index(face, character), FT_LOAD_DEFAULT);

	FT_Glyph glyph;
	FT_Get_Glyph(face->glyph, &glyph);

	FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
	FT_BitmapGlyph bitmap_glyph = FT_BitmapGlyph(glyph);

	FT_Bitmap & bitmap(bitmap_glyph->bitmap);

	int width(next_power_of_two(bitmap.width));
	int height(next_power_of_two(bitmap.rows));

	uchar * expanded_data = new uchar[2*width*height];

	for( int j(0); j<height; j++ )
		for( int i(0); i<width; i++ )
			expanded_data[2*(i+j*width)] = expanded_data[2*(i+j*width)+1] = (i >= int(bitmap.width) || j >= int(bitmap.rows)) ? 0 : bitmap.buffer[i+bitmap.width*j];

	glBindTexture(GL_TEXTURE_2D, m_Textures[int(character)]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);

	delete [] expanded_data;

	glNewList(m_ListBase + character, GL_COMPILE);
	  glBindTexture(GL_TEXTURE_2D, m_Textures[int(character)]);
	  glPushMatrix();
	    glTranslatef(bitmap_glyph->left, bitmap_glyph->top - bitmap.rows, 0);

	    float x(float(bitmap.width) / float(width));
	    float y(float(bitmap.rows) / float(height));

	    glBegin(GL_QUADS);
	      glTexCoord2d(0, 0); glVertex2f(0, bitmap.rows);
	      glTexCoord2d(0, y); glVertex2f(0, 0);
	      glTexCoord2d(x, y); glVertex2f(bitmap.width, 0);
	      glTexCoord2d(x, 0); glVertex2f(bitmap.width, bitmap.rows);
	    glEnd();
	  glPopMatrix();
	  glTranslatef(face->glyph->advance.x >> 6 ,0,0);
	glEndList();
}

void CFont::_push_matrix() const
{
	glPushAttrib(GL_TRANSFORM_BIT);
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(viewport[0], viewport[2], viewport[1], viewport[3]);
	glPopAttrib();
}

void CFont::_pop_matrix() const
{
	glPushAttrib(GL_TRANSFORM_BIT);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
}
