/*
*   SNAKE: THE GAME
*   coded by Ashwin Abraham (210050023) (21/04/2022)
*/

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

//key encodings of the arrow keys
#define LEFT_ARROW 65361
#define UP_ARROW 65362
#define RIGHT_ARROW 65363
#define DOWN_ARROW 65364

const int PW = 20; //width of each Pixel
const int PH = 20; //height of each Pixel
const int DIM_X = 600; //width of the screen
const int DIM_Y = 600; //height of the screen
const int move_len = 20; //step size
const double time_step = 0.1; //time step (determines speed of the snake)


//objects of this class cover the screen 
//They are usually not visible, but when shown they make up the green pixels of the snake
//and the red pixels of its food
class Pixel: public Fl_Widget {
	private:
		int x, y;
		Fl_Color col;

		void draw()
		{
			fl_color(col);
			fl_rectf(x, y, PW, PH, col);
		}

	public:
		Pixel(int x, int y, Fl_Color col = FL_GREEN):
			Fl_Widget(x, y, PW, PH), x(x), y(y), col(col){}
		
		virtual ~Pixel() = default;
};

//objects of this class make up each component of the snake's body
class Piece {
	int x, y, dir; //dir represents the direction of motion of the piece
					//it is numerically equal to the key encoding of the arrow key corresponding to the direction of motion

	Piece(int x, int y, int dir):
		x(x), y(y), dir(dir){}

	void move()
	{
		x = next_x();
		y = next_y();
	}

	int next_x() const
	{
		return x + ((dir - UP_ARROW)%2)*move_len;
	}

	int next_y() const
	{
		return y + ((dir - RIGHT_ARROW)%2)*move_len;
	}

	//all members of this class are private
	//since they must only be accessed by an instantiated in the Snake and Handler classes and the update_win callback function
	friend class Snake;
	friend class Handler;
	friend void update_win(void*);
};


//An object of this class is created which represents the snake
class Snake {
	private:
		//dynamic array of pieces of the snake
		std::vector<Piece*> snake;
	public:
		Snake(int num = 1, int x = 0, int y = DIM_Y/2, int dir = RIGHT_ARROW)
		{
			for(int i = 0; i<num; ++i) snake.push_back(new Piece(x + i*PW, y, dir));
		}

		void add(Piece* piece)
		{
			snake.push_back(piece);
		}

		//note: So that inserting pieces can be done efficiently (in O(1)), the head of the snake is the last element of the array
		//and the tail of the snake is the first element of the array

		Piece* head()
		{
			return snake[size()-1];
		}

		Piece* tail()
		{
			return snake[0];
		}

		//returns ith piece of the snake
		Piece* operator[](unsigned int i){
			return snake[i];
		}

		int size() const
		{
			return snake.size();
		}

		//checks if a point lies on the snake (including head)
		bool intersects(int x, int y) const
		{
			for(int i = 0; i<size(); ++i)
			{
				if(snake[i]->x == x && snake[i]->y == y)
					return true;
			}
			return false;
		}

		//checks if the head intersects any part of the snake
		bool self_intersects() const
		{
			for(int i = 0; i<(size()-1); ++i)
			{
				if(snake[i]->x == snake[size()-1]->x && snake[i]->y == snake[size()-1]->y)
					return true;
			}
			return false;
		}

		//checks if the head intersects the screen's boundary
		bool intersects_boundary() const
		{
			bool x_in = snake[size()-1]->x < 0 || snake[size()-1]->x >= DIM_X;
			bool y_in = snake[size()-1]->y < 0 || snake[size()-1]->y >=DIM_Y;
			return x_in || y_in;
		}

		virtual ~Snake()
		{
			for(int i = 0; i<size(); ++i)
			{
				delete snake[i];
			}
		}
		
} snake;


//this class is used to handle events from the keyboard
class Handler: public Fl_Widget {
	public:
		//since Handler is not being drawn, this function is just so that Handler can be instantiated
		Handler():
			Fl_Widget(0, 0, 0, 0){}

		//method that handles events from the keyboard
		int handle(int event)
		{
			if(event == FL_FOCUS)
				return 1;

			if(event == FL_KEYDOWN)
			{
				int event_key = Fl::event_key();

				//adding support for WASD keys along with arrow keys
				switch(event_key)
				{
					case 'w':
						event_key = UP_ARROW;
						break;
					
					case 'a':
						event_key = LEFT_ARROW;
						break;
					
					case 's':
						event_key = DOWN_ARROW;
						break;

					case 'd':
						event_key = RIGHT_ARROW;
						break;
				}

				//preventing snake from being able to turn back 
				//(go immediately in the opposite direction of its motion)
				if(snake.size() > 1){
					if(snake[snake.size()-2]->y == snake[snake.size()-1]->y){
						if(event_key%2)
							return 1;
					}
					else if(snake[snake.size()-2]->x == snake[snake.size()-1]->x){
						if(event_key%2 == 0)
							return 1;
					}
				}
			
				snake.head()->dir = event_key;
				return 1;
			}

			return 0;
		}

		//since drawing is done via showing and hiding pixels,
		//this function exist so that Handler is not an abstract class and can be instantiated
		void draw(){}

		virtual ~Handler() = default;
};

//when visible, form the body of the snake
std::vector<std::vector<Pixel*> > green_pixels;

//when visible, form the food eaten by the snake
std::vector<std::vector<Pixel*> > red_pixels;

//displays GAME OVER when game is over
Fl_Box* Game_Over_Box;

//displays score on the top right corner of the screen
Fl_Box* score_box;


//This callback function is repeatedly executed throughout the game
//It updates the window (changes the display) and moves the snake and displays the food of the snake
//It also determines whether game is over or not
void update_win(void* data)
{
	Fl_Window* winptr = reinterpret_cast<Fl_Window*>(data);

	//manages score_box
	static int score = 0;
	score_box->copy_label(("SCORE: " + std::to_string(score)).c_str());
	winptr->add(score_box);

	//places food (a single red pixel) on random locations on screen (not on snake or score_box)
	static bool eaten = true;
	static int loc_x, loc_y;
	if(eaten)
	{
		do{
			loc_x = PW*(rand()%(DIM_X/PW));
			loc_y = PH*(rand()%(DIM_Y/PH));
		} while(snake.intersects(loc_x, loc_y) || (loc_x-0.8*DIM_X+PW>=0 && loc_y<=0.05*DIM_Y));

		winptr->add(red_pixels[loc_x/PW][loc_y/PH]);
		eaten = false;
	}

	//adds piece to snake when it eats food
	if(snake.head()->next_x() == loc_x && snake.head()->next_y() == loc_y)
	{
		int dir = snake.head()->dir;
		snake.add(new Piece(loc_x, loc_y, dir));
		winptr->remove(red_pixels[loc_x/PW][loc_y/PH]);
		winptr->add(green_pixels[loc_x/PW][loc_y/PH]);
		eaten = true;
		++score;
	}

	//moves snake
	winptr->remove(green_pixels[snake.tail()->x/PW][snake.tail()->y/PH]);
	for(int i = 0; i<snake.size(); ++i)
	{
		snake[i]->move();

		if(i!=snake.size()-1)
			snake[i]->dir = snake[i+1]->dir;
	}

	//checks if Game is over or not
	if(!snake.self_intersects() && !snake.intersects_boundary())
	{
		winptr->add(green_pixels[snake.head()->x/PW][snake.head()->y/PH]);
		winptr->redraw();
		Fl::repeat_timeout(time_step, update_win, data);
	}
	else
	{
		winptr->add(Game_Over_Box);
		winptr->redraw();
	}
}



int main(int argc, char** argv)
{
	srand(time(NULL));

	//filling screen with hidden pixels for snake and its food
	for(int i = 0; i<DIM_X/PW; ++i)
	{
		green_pixels.push_back(std::vector<Pixel*>());
		red_pixels.push_back(std::vector<Pixel*>());

		for(int j = 0; j<DIM_Y/PH; ++j)
		{
			green_pixels[i].push_back(new Pixel(PW*i, PH*j, FL_GREEN));
			red_pixels[i].push_back(new Pixel(PW*i, PH*j, FL_RED));
		}
	}

	//Setting attributes of Game_Over_Box
	Game_Over_Box = new Fl_Box(0.2*DIM_X, 0.4*DIM_Y, 0.6*DIM_X, 0.2*DIM_Y, "GAME OVER");
	Game_Over_Box->box(FL_FLAT_BOX);
	Game_Over_Box->labelfont(FL_BOLD);
	Game_Over_Box->labelsize(40);
	Game_Over_Box->labelcolor(FL_RED);
	Game_Over_Box->color(FL_BLACK);

	//setting attributes of score_box
	score_box = new Fl_Box(0.8*DIM_X, 0, 0.2*DIM_X, 0.05*DIM_Y);
	score_box->labelcolor(FL_YELLOW);
	score_box->labelfont(FL_BOLD);
	score_box->labelsize(20);

	//creating a window and a handler
	Fl_Window* window = new Fl_Window (DIM_X, DIM_Y,"SNAKE");
	Handler handler;

	//causes callback function to be called in intervals of time_step
	Fl::add_timeout(time_step, update_win, window);

	//setting attributes of window
	window->color(FL_BLACK);
	window->end();
	window->show();

	return Fl::run();
}
