#include "ground.h"


CGround::CGround() : CScopeLogger(__FUNCTION__){}

CGround::~CGround(){}

void CGround::generate( const int width, const int height )
{
	int wr(20);
	std::vector<double> data(width*height);
	std::vector<double> gk(2*wr+1);
	double p(0.005), sigma(5.0), sum1, sum2, max(0.0);


	m_Width  = width;
	m_Height = height;
	m_Data   = std::vector<double>(width*height);

	// initialization with random seeds
	std::fill(data.begin(), data.end(), 0.0);

	for( std::size_t k=0; k<data.size(); k++ )
		if( uniform<float>() < p )
			data[k] = 1.0;

	/* (for debugging)
	data[(height/2-50)*width+(width/2-50)] = 1.0;
	data[(height/2-50)*width+(width/2+50)] = 1.0;
	data[(height/2+50)*width+(width/2-50)] = 1.0;
	data[(height/2+50)*width+(width/2+50)] = 1.0;*/

	// gaussian smoothing
	for( int k=-wr; k<=+wr; k++ )
			gk[k+wr] = exp(-sq(k)/(2.0*sq(sigma)));

	for( int it=0; it<3; it++ )
	{
		for( int y=0; y<height; y++ )
		{
			for( int x=0; x<width; x++ )
			{
				sum1 = sum2 = 0.0;

				for( int xx=-wr; xx<=+wr; xx++ )
				{
					int xxx = (x + xx);

					if( xxx>=0 && xxx<width )
					{
						sum1 += data[y*width+xxx] * gk[xx+wr];
						sum2 += gk[xx+wr];
					}
				}

				m_Data[y*width+x] = (sum1 / sum2);
			}
		}

		data = m_Data;

		for( int y=0; y<height; y++ )
		{
			for( int x=0; x<width; x++ )
			{
				sum1 = sum2 = 0.0;

				for( int yy=-wr; yy<=+wr; yy++ )
				{
					int yyy = (y + yy);

					if( yyy>=0 && yyy<height )
					{
						sum1 += data[yyy*width+x] * gk[yy+wr];
						sum2 += gk[yy+wr];
					}
				}

				m_Data[y*width+x] = (sum1 / sum2);
			}
		}

		data = m_Data;
		max = 0.0;

		for( std::size_t i=0; i<data.size(); i++ )
			max = std::max(max, data[i]);
	}

	// normalization
	for( std::size_t k=0; k<m_Data.size(); k++ )
		m_Data[k] /= max;
}

double & CGround::operator () ( const int x, const int y )
{
	if( !(x>=0 && x<m_Width && y>=0 && y<m_Height) )
		std::cout << "bad coords !!!! -> (" << x << ", " << y << ")\n";
	assert(x>=0 && x<m_Width && y>=0 && y<m_Height);
	return m_Data[y*m_Width+x];
}

void CGround::render( IWindow *window ) const
{
	for( int y=0; y<window->height(); y++ )
	{
		for( int x=0; x<window->width(); x++ )
		{
			double p = m_Data[y*window->width()+x];
			window->set_pixel(x, y, color4f(color3f(p, p, p), 1.0f));
		}
	}
}
