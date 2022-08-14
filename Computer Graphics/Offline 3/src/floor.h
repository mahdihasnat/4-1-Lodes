#ifndef FB5DDE1F_8D91_4F02_A735_C37A7016D910
#define FB5DDE1F_8D91_4F02_A735_C37A7016D910

#include "object.h"

template<typename T>
class Floor: public Object<T>
{
public:
	const int tile_size = 20;
	const int tile_count = 20;
	void draw()
	{
		for(int rot=0;rot<4;rot++)
		{
			glPushMatrix();
			glRotatef(90*rot,0,0,1);
			for(int i=0,x=0;i<tile_count;i++,x+=tile_size)
			{
				for(int j=0,y=0;j<tile_count;j++,y+=tile_size)
				{
					glBegin(GL_QUADS);{
						if((i+j+rot)%2)
							glColor3d(0,0,0);
						else
							glColor3d(1,1,1);
						glVertex3i(x,y,0);
						glVertex3i(x,y+tile_size,0);
						glVertex3i(x+tile_size,y+tile_size,0);
						glVertex3i(x+tile_size,y,0);
					}
					glEnd();
				}
			}
			glPopMatrix();
		}
	}
};

#endif /* FB5DDE1F_8D91_4F02_A735_C37A7016D910 */
