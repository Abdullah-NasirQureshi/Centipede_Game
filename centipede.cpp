#include <iostream>

#include<ctime>

#include <SFML/Graphics.hpp>

#include <SFML/Audio.hpp>



using namespace std;



// Initializing Dimensions.

// resolutionX and resolutionY determine the rendering resolution.

// Don't edit unless required. Use functions on lines 43, 44, 45 for resizing the game window.

const int resolutionX = 960;

const int resolutionY = 960;

const int boxPixelsX = 32;

const int boxPixelsY = 32;

const int gameRows = resolutionX / boxPixelsX; // Total rows on grid

const int gameColumns = resolutionY / boxPixelsY; // Total columns on grid



// Initializing GameGrid.

int gameGrid[gameRows][gameColumns] = {};



// The following exist purely for readability.

const int x = 0;

const int y = 1;

const int exists = 2;



//THIS FUNCTION DRAWS THE PLAYER WHEN CALLED, I HAVE MADE THIS FUNCTION SO THAT I MAY NOT NEED TO DRAW THE PLAYER BY SPECIFYING EACH AND EVERY CHARACTER OF THE PLAYER AGAIN. 

void drawPlayer(sf::RenderWindow& window, float player[], sf::Sprite& playerSprite);

//THIS FUNCTION DRAWS THE death pic WHEN CALLED, I HAVE MADE THIS FUNCTION SO THAT I MAY NOT NEED TO DRAW THE death pic BY SPECIFYING EACH AND EVERY CHARACTER OF THE death pic AGAIN. 

void drawPop(sf::RenderWindow& window, float pop[], sf::Sprite& popSprite, sf::Clock& levelClock);


//THIS FUNCTION MOVES THE BULLET BIT BY BIT WHEN CALLED,  I HAVE MADE THIS FUNCTION SO THAT EACH TIME THE BULLET IS FIRED, THIS FUNCTION CHANGES THE POSITION OF THE BULLET ACROSS THE SCREEN SMOOTHLY.

void moveBullet(float bullet[3], float Mushroom[][3], sf::Clock& bulletClock);

//THIS FUNCTION DRAWS THE BULLET WHEN CALLED, I HAVE MADE THIS FUNCTION SO THAT I MAY NOT NEED TO DRAW THE BULLET BY SPECIFYING EACH AND EVERY CHARACTER OF THE BULLET AGAIN. 

void drawBullet(sf::RenderWindow& window, float bullet[3], sf::Sprite& bulletSprite);

//THIS FUNCTION DRAWS THE MUSHROOM WHEN CALLED I HAVE MADE THIS FUNCTION SO THAT I MAY NOT NEED TO DRAW THE MUSHROOM BY SPECIFYING EACH AND EVERY CHARACTER OF THE MUSHROOM AGAIN. 

void drawMushroom(sf::RenderWindow& window, float mushroom[][3], sf::Sprite mushroomSprite, int numMushroom, int mushroomShot[], int* extra);

//THIS FUNCTION DRAWS THE CENTIPEDE WHEN CALLED I HAVE MADE THIS FUNCTION SO THAT I MAY NOT NEED TO DRAW THE CENTIPEDE BY SPECIFYING EACH AND EVERY CHARACTER OF THE CENTIPEDE AGAIN. 

void drawCentipede(sf::RenderWindow& window, float centipede[12][3], sf::Sprite& centipedeSprite);


//THIS FUNCTION DRAWS THE CENTIPEDEHEAD WHEN CALLED I HAVE MADE THIS FUNCTION SO THAT I MAY NOT NEED TO DRAW THE CENTIPEDEHEAD BY SPECIFYING EACH AND EVERY CHARACTER OF THE CENTIPEDEHEAD AGAIN. 

void drawCentipedeHead(sf::RenderWindow& window, float centipedeHead[][3], sf::Sprite& centipedeHeadSprite);

//THIS FUNCTION DRAWS THE EXTRACENTIPEDEHEADS WHEN CALLED I HAVE MADE THIS FUNCTION SO THAT I MAY NOT NEED TO DRAW THE EXTRACENTIPEDEHEADS BY SPECIFYING EACH AND EVERY CHARACTER OF THE EXTRACENTIPEDEHEADS AGAIN. 

void drawExtraCentipedeHead(sf::RenderWindow& window, float extraCentipedeHead[][3], sf::Sprite& extraCentipedeHeadSprite);

//THIS FUNCTION MOVES THE centipede WHEN CALLED, I HAVE MADE THIS FUNCTION SO THAT IN EACH ITERATION WHEN THIS FUNCTION IS CALLED, THE CENTIPEDE MOVES 32 PIXELS

void moveCentipedeLeft(float centipede[12][3], float centipedeHead[][3],float mushroom[][3], sf::Clock& centipedeClock, bool centiFace[], int randomStart, int* numMushroom, int mushroomShot[], int* Level, int*centiSpeed, float ExtraCentipedeHead[][3], bool centiHead[], int &killedHeads, bool &shouldMove, bool go[], int &badMushroom, int &extra,int &numMush, float scorp[], float spider[]);

//THIS FUNCTION DRAWS THE SPIDER WHEN CALLED I HAVE MADE THIS FUNCTION SO THAT I MAY NOT NEED TO DRAW THE SPIDER BY SPECIFYING EACH AND EVERY CHARACTER OF THE SPIDER AGAIN. 

void drawSpider(sf::RenderWindow& window, float spider[], sf::Sprite& spiderSprite);

//THIS FUNCTION MOVES THE SPIDER WHEN CALLED, I HAVE MADE THIS FUNCTION SO THAT IN EACH ITERATION WHEN THIS FUNCTION IS CALLED, THE SPIDER MOVES AS NEEDED

void moveSpider(float spider[3], sf::Clock& spiderClock);

//THIS FUNCTION DRAWS THE SCORPIAN WHEN CALLED I HAVE MADE THIS FUNCTION SO THAT I MAY NOT NEED TO DRAW THE SCORPIAN BY SPECIFYING EACH AND EVERY CHARACTER OF THE SCORPIAN AGAIN. 

void drawScorp(sf::RenderWindow& window, float scorp[], sf::Sprite& scorpSprite);

//THIS FUNCTION MOVES THE SCORPIAN WHEN CALLED, I HAVE MADE THIS FUNCTION SO THAT IN EACH ITERATION WHEN THIS FUNCTION IS CALLED, THE SCORPIAN MOVES 32 PIXELS

void moveScorp(float scorp[3], sf::Clock& scorpClock);


//THIS FUNCTION splits THE centipede WHEN CALLED, I HAVE MADE IT A FUNCTION SO THAT EACH TIME THE BULLET MATCHES CENTPEDE, THIS FUNCTION HELPS IN SPLITING IT AND I DONT NEED MAKE THE CONDITIONS IT REPEATEDLY

void splitCentipede(float centipede[12][3], float centipedeHead[][3], sf::Clock& centipedeClock, bool centiFace[],float bullet[3], int *extra,float mushroom[][3], int* score, int *badMushroom, int* choice);

//THIS FUNCTION DRAWS THE FLEA WHEN CALLED I HAVE MADE THIS FUNCTION SO THAT I MAY NOT NEED TO DRAW THE FLEA BY SPECIFYING EACH AND EVERY CHARACTER OF THE FLEA AGAIN. 

void drawFlee(sf::RenderWindow& window, float flee[], sf::Sprite& fleeSprite);

//THIS FUNCTION MOVES THE FLEA WHEN CALLED, I HAVE MADE THIS FUNCTION SO THAT IN EACH ITERATION WHEN THIS FUNCTION IS CALLED, THE FLEA MOVES 32 PIXELS

void moveFlee(float flee[3], sf::Clock& fleeClock, float mushroom[][3], int &countingFleeMush);


//THIS FUNCTION MOVES THE EXTRAHEADS WHEN CALLED, I HAVE MADE THIS FUNCTION SO THAT IN EACH ITERATION WHEN THIS FUNCTION IS CALLED, THE EXTRAHEADS MOVES 32 PIXELS

void moveExtraHeads(float centipede[][3], float centipedeHead[][3],float mushroom[][3], sf::Clock& ExtraCentipedeHeadClock, bool centiFace[], int randomStart, int* numMushroom, int mushroomShot[], int &Level, int*centiSpeed, float ExtraCentipedeHead[][3], bool centiHead[], bool go[], bool &shouldMove, int &killedHeads);

//THIS FUNCTION UPDATES THE LEVEL, I HAVE MADE IT A FUNCTION SO THAT WHEN CENTIPEDE IS KILLED, THIS FUNCTION MAY BE CALL THE REDEFINE ALL THE NECESSARY ARRAYS
void LevelUp( float centipede[12][3], float centipedeHead[][3],float mushroom[][3], sf::Clock& centipedeClock, bool centiFace[], int* numMushroom, int mushroomShot[], int &randomStart, int &killedHeads, bool &shouldMove, bool go[], float ExtraCentipedeHead[][3], int &badMushroom, int &extra, int &Level1, float scorp[], float spider[]);

//THIS FUNCTION MOVES THE FAST MOVING CENTIPEDE WHEN CALLED, I HAVE MADE THIS FUNCTION SO THAT IN EACH ITERATION WHEN THIS FUNCTION IS CALLED, THE FAST MOVING CENTIPEDE MOVES 32 PIXELS

void moveFastCentipedeLeft(float centipede[12][3], float centipedeHead[][3],float mushroom[][3], sf::Clock& centipedeFastClock, bool centiFace[], int randomStart, int* numMushroom, int mushroomShot[], int* Level, int*centiSpeed, float ExtraCentipedeHead[][3], bool centiHead[], int &killedHeads, bool &shouldMove, bool go[], int &badMushroom, int &extra, int &numMush, float scorp[], float spider[]);



int main()

{
	int level=1;
	int *Level = &level; 


	srand(time(0));

	// Declaring RenderWindow.

	sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "Centipede", sf::Style::Close | sf::Style::Titlebar);

	window.setSize(sf::Vector2u(640, 640));
	// Used to position your window on every launch. Use according to your needs.
	window.setPosition(sf::Vector2i(100, 0));


	// Initializing Background Music.

	sf::Music bgMusic;
	bgMusic.openFromFile("Music/field_of_hopes.ogg");
	bgMusic.play();
	bgMusic.setVolume(50);


	// Initializing Background 1.

	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	backgroundTexture.loadFromFile("Textures/background8.jpg");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setColor(sf::Color(255, 255, 255, 255 ));
	 

	
	// Initializing Background 2.

	sf::Texture background1Texture;
	sf::Sprite background1Sprite;
	background1Texture.loadFromFile("Textures/back6.jpg");
	background1Sprite.setTexture(background1Texture);
	background1Sprite.setColor(sf::Color(255, 255, 255, 255 ));
	background1Sprite.setScale(2.0f, 2.9f);


	// Initializing Background 3.

	sf::Texture background3Texture;
	sf::Sprite background3Sprite;
	background3Texture.loadFromFile("Textures/back4.jpg");
	background3Sprite.setTexture(background3Texture);
	background3Sprite.setColor(sf::Color(255, 255, 255, 255 ));
	background3Sprite.setScale(1.0f, 1.9f);


	// Initializing Background for game over.

	sf::Texture background2Texture;
	sf::Sprite background2Sprite;
	background2Texture.loadFromFile("Textures/gameover1.jpg");
	background2Sprite.setTexture(background2Texture);
	background2Sprite.setColor(sf::Color(255, 255, 255, 255*0.4 )); 




	// Initializing Player and Player Sprites.

	float player[3] = {};
	player[x] = (gameColumns / 2) * boxPixelsX;
	player[y] = 800;//(gameColumns * 3 / 4) * boxPixelsY;
	player[exists] = true;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	playerTexture.loadFromFile("Textures/player.png");
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));


	// Initializing death pic and death Sprites.
	float pop[3] = {};
	pop[x] = 0;
	pop[y] = 0;
	pop[exists] = false;
	sf::Clock levelClock;
	sf::Texture popTexture;
	sf::Sprite popSprite;
	popTexture.loadFromFile("Textures/death.png");
	popSprite.setTexture(popTexture);
	popSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));


	// Initializing bullet and bullet Sprites.

	float bullet[3] = {};
	bullet[x] = player[x];
	bullet[y] = player[y] - boxPixelsY;
	bullet[exists] = false;
	sf::Clock bulletClock;
	sf::Texture bulletTexture;
	sf::Sprite bulletSprite;
	bulletTexture.loadFromFile("Textures/bullet.png");
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

	
	// Initializing Mushroom and Mushroom Sprites.	
	
	//number of mushrooms on screen
	int numMushroom = 0;

	numMushroom = ((rand()%10)+1)+20;

	int mushroomShot[300]={0};
	float mushroom[300][3] = {};
	mushroom[0][x] = 32*15;
	mushroom[0][y] = 768 ;
	mushroom[1][x] = 32*12;
	mushroom[1][y] = 768 ;
	mushroom[2][x] = 32*22;
	mushroom[2][y] = 768 ;


	for(int p=3; p<300; p++)
	{
	 	mushroom[p][x] = ((rand()%29)*boxPixelsX)+32;
	 	mushroom[p][y] = ((rand()%27)*boxPixelsY)+32;
	}



	for(int p=0; p<numMushroom; p++)
	{
		mushroom[p][exists] = true;
	}	

	for(int p=199; p<300; p++)
	{
		mushroom[p][exists] = false;
	}

	

	sf::Texture mushroomTexture;
	sf::Sprite mushroomSprite;
	mushroomTexture.loadFromFile("Textures/mushroom.png");
	mushroomSprite.setTexture(mushroomTexture);
	mushroomSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
	srand(time(0));


	//Initializing Centipede and Centipede Sprites.

	float centipede[12][3] = {};
	int randomStart = ((rand()%29)+1)*32;
	for( int h=0; h<12 ; h++)
	{
	centipede[h][x] = randomStart+(32*h);
	centipede[h][y] = 0;
	centipede[h][exists] = true;
	}

	sf::Clock centipedeClock;
	sf::Texture centipedeTexture;
	sf::Sprite centipedeSprite;

	centipedeTexture.loadFromFile("Textures/c_body_left_walk.png");
	centipedeSprite.setTexture(centipedeTexture);
	centipedeSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

	//Initializing Centipede Head and Centipede Head Sprites.

	float centipedeHead[12][3];

	for(int g=0; g<12; g++)
	{
		centipedeHead[g][x]=centipede[g][x];
		centipedeHead[g][y]=centipede[g][y];
		centipedeHead[g][exists] = false;
	}
	
	centipedeHead[0][exists]=true;
	sf::Texture centipedeHeadTexture;
	sf::Sprite centipedeHeadSprite;
	centipedeHeadTexture.loadFromFile("Textures/c_head_left_walk.png");
	centipedeHeadSprite.setTexture(centipedeHeadTexture);
	centipedeHeadSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));


	//Initializing Centipede Heads that appear when real centipede is in the player area.

	sf::Clock centipedeFastClock;
	float ExtraCentipedeHead[12][3];

	for(int g=0; g<12; g++)
	{
		if(g%2==0)
		{
		ExtraCentipedeHead[g][x]=960;
		}
		if(g%2==1)
		{
		ExtraCentipedeHead[g][x]=0;
		}
		ExtraCentipedeHead[g][y] = (rand()%10)*32;
		ExtraCentipedeHead[g][exists] = false;
	}

	sf::Clock ExtraCentipedeHeadClock;
	sf::Texture ExtraCentipedeHeadTexture;
	sf::Sprite ExtraCentipedeHeadSprite;
	ExtraCentipedeHeadTexture.loadFromFile("Textures/c_head_left_walk.png");
	ExtraCentipedeHeadSprite.setTexture(ExtraCentipedeHeadTexture);
	ExtraCentipedeHeadSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

	//Direction in which centipede head is moving (true for right and false for left)

	bool centiHead [12];

	for(int m=0; m<12; m++)
	{
		if(m%2==0)
		{
		centiHead[m] = false; 
		}
		if(m%2==1)
		{
		centiHead[m] = true; 
		}
	}


	// Initializing spider Sprites.


	float spider[3] = {};
	spider[x] = 0;
	spider[y] = 928;	
	spider[exists] = true;
	sf::Clock spiderClock;
	sf::Texture spiderTexture;
	sf::Sprite spiderSprite;
	spiderTexture.loadFromFile("Textures/spider_and_score.png");
	spiderSprite.setTexture(spiderTexture);
	spiderSprite.setTextureRect(sf::IntRect(0, 0, 2*boxPixelsX, boxPixelsY));


	// Initializing scorpian Sprites.

	float scorp[3] = {};
	scorp[x] = -32*5;
	scorp[y] = (rand()%20)*32;
	scorp[exists] = true;
	sf::Clock scorpClock;
	sf::Texture scorpTexture;
	sf::Sprite scorpSprite;
	scorpTexture.loadFromFile("Textures/scorpion.png");
	scorpSprite.setTexture(scorpTexture);
	scorpSprite.setTextureRect(sf::IntRect(0, 0, 2*boxPixelsX, boxPixelsY));


	// Initializing flee Sprites.

	float flee[3] = {};
	flee[x] = ((rand()%30)+1)*32;
	flee[y] = 0;//((rand()%30)+1)*32;
	flee[exists] = true;
	sf::Clock fleeClock;
	sf::Texture fleeTexture;
	sf::Sprite fleeSprite;
	fleeTexture.loadFromFile("Textures/flea.png");
	fleeSprite.setTexture(fleeTexture);
	fleeSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));


	//Initializing bullet sound;
	
	sf::SoundBuffer bsound;	 
	(bsound.loadFromFile("Sound Effects/fire1.wav")) ;
    sf::Sound bb;
    bb.setBuffer(bsound);

    //Initializing player died sound;
	
	sf::SoundBuffer psound;	 
	(psound.loadFromFile("Sound Effects/spider.wav")) ;
    sf::Sound pp;
    pp.setBuffer(psound);


	// Score of the player
	int score = 0;

	
	//Direction in which centipede is moving (true for right and false for left)
	bool centiFace [12];


	for(int m=0; m<12; m++)
	{
		centiFace[m] = false; 
	}

	
	//Number of the Mushrooms made after bullet hits the centipate
	int extra = 200;

	//Number of the Poisnous Mushrooms made after bullet hits the centipate
	int badMushroom = 250;

	// variable that counts the number of times spider have passed over the mushroom so that it randomly eats mushroom
	int countSpiderEat = 3235;

	//Player lives
	int chances = 5;
	int *Chances = &chances;

	// number of mushrooms in player area
	int countBigger = 0;

	//speed of centipede
	int centiSpeed = 110;

	//Tells if flee should be drawn or not
	bool FleeDraw = false;

	//shows if the extra centipede head should move or not
	bool go[12];
	bool shouldMove = false;

	//setting all true 
	for(int i=0; i<12; i++)
	{
	go[i]=true;
	}

	//mushroomsi in next level
	int numMush = 2;

	//counts the number of extra heads killed

	int killedHeads = 0;

	//change the mushroom to poisnous
	int poisnous = 1;
	bool checkPoison = false;

	//determines the position of mushroom drawn when flee passes
	int countingFleeMush = 1;


	while(window.isOpen()) {


	//Different backgrouns for different levels

		if(*Level % 3 == 1)
		{
			window.draw(backgroundSprite);
		}

		if(*Level % 3 == 0)
		{
			window.draw(background1Sprite);
		}

		if(*Level % 3 == 2)
		{
			window.draw(background3Sprite);
		}

		//Number that alligns the mushrooms that should be done true may be
		int newd = 1;


		drawPlayer(window, player, playerSprite);

		splitCentipede(centipede,centipedeHead,  centipedeClock, centiFace, bullet, &extra, mushroom, &score, &badMushroom, Level);

		drawMushroom(window, mushroom, mushroomSprite, numMushroom, mushroomShot, &extra);

		drawCentipede(window, centipede, centipedeSprite);

		moveCentipedeLeft(centipede, centipedeHead, mushroom, centipedeClock, centiFace,randomStart, &numMushroom, mushroomShot, Level, &centiSpeed, ExtraCentipedeHead, centiHead, killedHeads, shouldMove, go, badMushroom, extra, newd, scorp, spider);

		moveFastCentipedeLeft(centipede, centipedeHead, mushroom, centipedeFastClock, centiFace,randomStart, &numMushroom, mushroomShot, Level, &centiSpeed, ExtraCentipedeHead, centiHead, killedHeads, shouldMove, go, badMushroom, extra, newd, scorp, spider);

		drawCentipede(window, centipede, centipedeSprite);

		drawCentipedeHead(window, centipedeHead, centipedeHeadSprite);

		drawExtraCentipedeHead(window, ExtraCentipedeHead, ExtraCentipedeHeadSprite);

		drawSpider(window, spider, spiderSprite );

		moveSpider(spider, spiderClock);

		drawScorp(window, scorp, scorpSprite );

		moveScorp(scorp, scorpClock);


		int countDown=0;

		for(int g=0; g<12; g++)
		{
			if(centipede[g][y]> 32*24)
			{
				countDown++;
			}
		}

		if(countDown==12)
		{
		 moveExtraHeads( centipede,  centipedeHead, mushroom, ExtraCentipedeHeadClock,  centiFace,  randomStart,  &numMushroom,  mushroomShot, level, &centiSpeed,  ExtraCentipedeHead, centiHead,  go,  shouldMove, killedHeads);
		}


		for(int i=0; i<300; i++)
		{
		if(mushroom[i][exists]==true)
		{
			if(mushroom[i][y] > 32*24)
			{
				countBigger++;
			}
		}
		}

		if(countBigger==3)
		{
			FleeDraw = true;
			flee[exists]= true;
		}

		

		
		//This syntax have been taking from an online source i.e. a ready made code on github
		//initializing text that needs to be output: score, levels and lives


		sf::Font font;
   		if (!font.loadFromFile("Roboto/Roboto-Black.ttf")) {
        // Handle loading error
    	    return EXIT_FAILURE;
    		}

    	sf::Text gameScore;
    	gameScore.setFont(font);
    	gameScore.setCharacterSize(30);
    	gameScore.setFillColor(sf::Color::White);
    	gameScore.setPosition(32*13, 928); // Adjust position as needed
     	gameScore.setString("SCORE : " + std::to_string(score));

     	sf::Text showLevels;
    	showLevels.setFont(font);
    	showLevels.setCharacterSize(30);
    	showLevels.setFillColor(sf::Color::White);
    	showLevels.setPosition(0, 928); // Adjust position as needed
     	showLevels.setString("LEVEL : " + std::to_string(*Level));

     	sf::Text showLives;
    	showLives.setFont(font);
    	showLives.setCharacterSize(30);
    	showLives.setFillColor(sf::Color::White);
    	showLives.setPosition(32*25, 928); // Adjust position as needed
     	showLives.setString("LIVES : " + std::to_string(*Chances));
	


       
		if (bullet[exists] == true) 
		{
			moveBullet(bullet, mushroom, bulletClock);

			drawBullet(window, bullet, bulletSprite );

			for(int p=0; p<300; p++)
			{

				if(bullet[x] == mushroom[p][x] && bullet[y]==mushroom[p][y])
				{
					mushroomShot[p]+=1;
				
					if(mushroom[p][exists]==true)
					{
						bullet[exists]=false;
					
						if(mushroomShot[p]>=2)
						{
							mushroom[p][exists]=false;
							score++;
						}

					}
				
				}

			}


		}

	if(spider[exists] == true)
	{
		for(int p=2; p<300; p++)
			{

			if((spider[x] == mushroom[p][x] && spider[y]==mushroom[p][y]) || (spider[x]+32 == mushroom[p][x] && spider[y]==mushroom[p][y]))
			{
			
				if(countSpiderEat%251==0)
				{
					mushroom[p][exists] = false;
					
				}
			}

			
		}

		countSpiderEat++;
	}
	


	if(scorp[exists] == true)
	{
		for(int p=2; p<250; p++)
		{

			if(scorp[x] == mushroom[p][x]+32 && scorp[y]==mushroom[p][y] && mushroom[p][exists]==true)
			{
				checkPoison = true;
				mushroom[p][exists] = false;
				mushroom[270+poisnous][x] = mushroom[p][x];
				mushroom[270+poisnous][y] = mushroom[p][y];
				mushroom[270+poisnous][exists] = true;
				poisnous++;
				break;		
			}
		
		}

		

		
	}
	


		


	for(int p=2; p<300; p++)
	{
		if(p>250)
		{
			if(mushroom[p][x]==player[x] && mushroom[p][y]==player[y] && player[exists] == true && mushroom[p][exists]==true)
			{
				*Chances -= 1;
				player[exists]=false;
				break;
			}
		}
	}


	if(player[exists]==true)
	{
		for(int c=0; c<12; c++)
		{
			if(centipedeHead[c][x] == player[x] && centipedeHead[c][y] == player[y] && centipedeHead[c][exists]==true)
			{

				pop[x]=player[x];
				pop[y]=player[y];
				pop[exists] = true;

				if(*Chances >= 0)
				{
					*Chances -= 1;
				}

				if(*Chances == 0)
				{
					player[exists] = false;
					drawPop(window, pop, popSprite, levelClock);
				}	
				player[exists]=false;

			}
		
		}

	}


	if(player[exists]==true)
	{
		for(int c=0; c<12; c++)
		{
			if(ExtraCentipedeHead[c][x] == player[x] && ExtraCentipedeHead[c][y] == player[y] && ExtraCentipedeHead[c][exists]==true)
			{

				pop[x]=player[x];
				pop[y]=player[y];
				pop[exists] = true;

				if(*Chances >= 0)
				{
					*Chances -= 1;
				}

				if(*Chances == 0)
				{
					player[exists] = false;
					drawPop(window, pop, popSprite, levelClock);
				}	
				player[exists]=false;

			}
		
		}

	}


	if(spider[exists] == true)
	{
		if((spider[x] == player[x] && spider[y] == player[y]) ||(spider[x]+32 == player[x] && spider[y] == player[y]) && player[exists] == true)
			{
				pop[x]=player[x];
				pop[y]=player[y];
				pop[exists] = true;

				if(*Chances >= 0)
				{
					*Chances -= 1;
				}

				if(*Chances == 0)
				{
					player[exists] = false;
					drawPop(window, pop, popSprite, levelClock);
				}	
				player[exists]=false;
				
				
			}
	}

	if(scorp[exists] == true)
	{
		if((scorp[x] == player[x] && scorp[y] == player[y]) ||(scorp[x]+32 == player[x] && scorp[y] == player[y]) && player[exists] == true)
			{
				pop[x]=player[x];
				pop[y]=player[y];
				pop[exists] = true;

				if(*Chances >= 0)
				{
					*Chances -= 1;
				}

				if(*Chances == 0)
				{
					player[exists] = false;
					drawPop(window, pop, popSprite, levelClock);
				}	
				player[exists]=false;
				
				
			}
	}


	if(spider[exists]==true)
	{
		if ((bullet[x] == spider[x] && bullet[y] >= spider[y]) || (bullet[x] == spider[x]+32 && bullet[y] >= spider[y]) && bullet[exists] == true)
		{
			spider[exists] = false;
			score += 300;
		}
	}

	if(scorp[exists]==true)
	{
		if(bullet[exists]==true)
		{
		if ((bullet[x] == scorp[x] && bullet[y] <= scorp[y]) || (bullet[x] == scorp[x]+32 && bullet[y] <= scorp[y]) )
		{
			bullet[exists]=false;
			scorp[exists] = false;
			score += 1000;
		}
	}

	}

	if(flee[exists]==true)
	{
		if (bullet[x] == flee[x] && bullet[y] <= flee[y] && bullet[exists] == true)
		{
			FleeDraw = false;
			bullet[exists]=false;
			flee[exists] = false;
		}
	}

	if(flee[exists]==true)
	{
		if(FleeDraw == true )
		{

		drawFlee(window, flee, fleeSprite);

		moveFlee(flee, fleeClock, mushroom, countingFleeMush);

		
		}
	}

	countBigger = 0;

	
	if(flee[x]==player[x] && flee[y]==player[y] && player[exists] == true && flee[exists]==true)
			{
				*Chances -= 1;
				player[exists]=false;
				
			}
			


	for(int j=0; j<12; j++)
	{
		if(bullet[x] == ExtraCentipedeHead[j][x] && bullet[y]==ExtraCentipedeHead[j][y] && bullet[exists]==true && ExtraCentipedeHead[j][exists] == true)
		{
			ExtraCentipedeHead[j][exists]=false;
			killedHeads++;
		}
	}

	if(player[exists]==false )
		{
			pp.play();
			window.draw(background2Sprite);
		}
	



		sf::Event e;

		while (window.pollEvent(e)) {

		if (e.type == sf::Event::Closed) 
		{
			return 0;
		}


		if(e.type == sf::Event::KeyPressed)
		{
			if(e.key.code == sf::Keyboard::Up)
			{
				if(player[y]<=960 && player[y]>=832)
				{
				player[y]-=32;
				break;
				}
			}

			else if(e.key.code == sf::Keyboard::Down)
			{
				if(player[y]<=896 && player[y]>=800)
				{
				player[y]+=32;
				break;
				}
			}

			else if(e.key.code == sf::Keyboard::Right)
			{	
				if(player[x]>=0 && player[x]<=896)
				{
				player[x]+=32;
				break;
				}
			}

			else if(e.key.code == sf::Keyboard::Left)
			{
				if(player[x]>=32 && player[x]<=960)
				{
				player[x]-=32;
				break;
				}
			}

			else if(e.key.code == sf::Keyboard::Space && bullet[exists] == false)
			{
				bb.play();
				if(bullet[exists]==false)
				{
					bullet[exists]=true;
					moveBullet(bullet, mushroom, bulletClock);
					drawBullet(window, bullet, bulletSprite);

					bullet[x] = player[x];

				bullet[y] = player[y] - boxPixelsY;
				}
				
			}

				break;
		}

	}		

		numMushroom++;
		if(numMushroom>199)
		{
			numMushroom=0;
		}

		window.draw(gameScore);
		window.draw(showLives);
		window.draw(showLevels);
		window.display();
		window.clear();

	}

}



////////////////////////////////////////////
//////  	FUNCTION DECLARATION    //////// 
////////////////////////////////////////////


void drawPlayer(sf::RenderWindow& window, float player[], sf::Sprite& playerSprite) {

	if(player[exists] == true)
	{
	playerSprite.setPosition(player[x], player[y]);
	window.draw(playerSprite);
	}

}


void drawPop(sf::RenderWindow& window, float pop[], sf::Sprite& popSprite, sf::Clock& levelClock) {
	
	if (levelClock.getElapsedTime().asMilliseconds() < 1000)
		return;

	levelClock.restart();

	if(pop[exists] == true)
	{
		//sf::sleep(sf::milliseconds(500));
		popSprite.setPosition(pop[x], pop[y]);
		window.draw(popSprite);

	}

}

void moveBullet(float bullet[3], float Mushroom[][3], sf::Clock& bulletClock) {

	if (bulletClock.getElapsedTime().asMilliseconds() < 4)

		return;

	bulletClock.restart();
	bullet[y] -= 32;	

	if (bullet[y] < -32)
	{
		bullet[exists] = false;
		
	}

}

void drawBullet(sf::RenderWindow& window, float bullet[3], sf::Sprite& bulletSprite) {

	bulletSprite.setPosition(bullet[x], bullet[y]);
	window.draw(bulletSprite);
}

void drawMushroom(sf::RenderWindow& window, float mushroom[][3], sf::Sprite mushroomSprite, int numMushroom, int mushroomShot[], int* extra)
{

	for(int i=0; i<300; i++)
	{
		if(i<250)
		{
		if(mushroom[i][exists]==false)
		{
			continue;
		}
		else if(mushroom[i][exists]==true && mushroomShot[i]==0)
		{
			mushroomSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
			mushroomSprite.setPosition(mushroom[i][x], mushroom[i][y]);
		}
		
		else if(mushroom[i][exists]==true && mushroomShot[i]==1)
		{
			mushroomSprite.setTextureRect(sf::IntRect(boxPixelsY, 0, boxPixelsX, boxPixelsY));
			mushroomSprite.setPosition(mushroom[i][x], mushroom[i][y]);
		}
		}


		else if(i>=250)
		{
			if(mushroom[i][exists]==true && mushroomShot[i]==0)
		{
			mushroomSprite.setTextureRect(sf::IntRect(0, boxPixelsY, boxPixelsX, boxPixelsY));
			mushroomSprite.setPosition(mushroom[i][x], mushroom[i][y]);
		}
		
		else if(mushroom[i][exists]==true && mushroomShot[i]==1)
		{
			mushroomSprite.setTextureRect(sf::IntRect(boxPixelsY, boxPixelsX, boxPixelsX, boxPixelsY));
			mushroomSprite.setPosition(mushroom[i][x], mushroom[i][y]);
		}
		}
		window.draw(mushroomSprite);
	}
}


void drawCentipedeHead(sf::RenderWindow& window, float centipedeHead[][3], sf::Sprite& centipedeHeadSprite)
{
	for(int i=0 ; i<12; i++)
	{
		if(centipedeHead[i][exists] == true)
		{
			centipedeHeadSprite.setPosition(centipedeHead[i][x], centipedeHead[i][y]);
			window.draw(centipedeHeadSprite);
		}
	}

}


void drawExtraCentipedeHead(sf::RenderWindow& window, float ExtraCentipedeHead[][3], sf::Sprite& ExtraCentipedeHeadSprite)
{
	for(int i=0 ; i<12; i++)
	{
		if(ExtraCentipedeHead[i][exists] == true)
		{
			ExtraCentipedeHeadSprite.setPosition(ExtraCentipedeHead[i][x], ExtraCentipedeHead[i][y]);
			window.draw(ExtraCentipedeHeadSprite);
		}
	}

}


void drawCentipede(sf::RenderWindow& window, float centipede[12][3], sf::Sprite& centipedeSprite)
{
	for(int i=0; i<12; i++)
	{
		if(centipede[i][exists]==true)
		{
		centipedeSprite.setPosition(centipede[i][x], centipede[i][y]);
		window.draw(centipedeSprite);
		}
	}

}

void moveFastCentipedeLeft(float centipede[12][3], float centipedeHead[][3],float mushroom[][3], sf::Clock& centipedeFastClock, bool centiFace[], int randomStart, int* numMushroom, int mushroomShot[], int* Level, int*centiSpeed, float ExtraCentipedeHead[][3], bool centiHead[], int &killedHeads, bool &shouldMove, bool go[], int &badMushroom, int &extra, int &numMush, float scorp[], float spider[])
{
	if (centipedeFastClock.getElapsedTime().asMilliseconds() < (*centiSpeed)-5)
		return;

	centipedeFastClock.restart();

	for(int h=12-(*Level)+1; h<12; h++)
	{
		
		if(centiFace[h]==false )
		{
			centipede[h][x]-=32;
			centipedeHead[h][x]=centipede[h][x];
			centipedeHead[h][y]=centipede[h][y];
		}

		for(int l=0; l<300; l++)
		{
			if(centiFace[h]==false)
			{
				if(centipede[h][x] == mushroom[l][x] && centipede[h][y] == mushroom[l][y] && mushroom[l][exists]==true)
				{
					centipede[h][y]+=32;
					//centiFace[h][1]=true;
					centiFace[h]=!centiFace[h];
					centipedeHead[h][x]=centipede[h][x];
					centipedeHead[h][y]=centipede[h][y];

				}
			}
			
			if(centiFace[h]==true)
			{
				if(centipede[h][x] == mushroom[l][x]-32 && centipede[h][y] == mushroom[l][y] && mushroom[l][exists]==true)
				{
					centipede[h][y]+=32;
					//centiFace[h][1]=true;
					centiFace[h]=!centiFace[h];
					centipedeHead[h][x]=centipede[h][x];
					centipedeHead[h][y]=centipede[h][y];

				}
			}
		}

		if(centipede[h][x] == -64 && centipede[h][y] <= 32*24)
		{
			centipede[h][y]+=32;
			centiFace[h]=!centiFace[h];
			centipedeHead[h][x]=centipede[h][x];
			centipedeHead[h][y]=centipede[h][y];
		}
		


		else if(centipede[h][x] == 960 && centipede[h][y]!= 0  && centipede[h][y]<=32*24)
			{
				centipede[h][y]+=32;
				centiFace[h]=!centiFace[h];
				centipedeHead[h][x]=centipede[h][x];
				centipedeHead[h][y]=centipede[h][y];
			}

		else if(centipede[h][x] == -64 && ((centipede[h][y]==32*24) || (centipede[h][y]==32*25) || (centipede[h][y]==32*26) || (centipede[h][y]==32*27)))
		{
			centipede[h][y]+=32;
			centiFace[h]=!centiFace[h];
			centipedeHead[h][x]=centipede[h][x];
			centipedeHead[h][y]=centipede[h][y];
		}


		else if(centipede[h][x] == 960 && ((centipede[h][y]==32*24) || (centipede[h][y]==32*25) || (centipede[h][y]==32*26) || (centipede[h][y]==32*27)))
			{
				centipede[h][y]+=32;
				centiFace[h]=!centiFace[h];
				centipedeHead[h][x]=centipede[h][x];
				centipedeHead[h][y]=centipede[h][y];
				centipedeHead[h][y]=centipede[h][y];
			}

		else if(centipede[h][x] == -64 &&  ((centipede[h][y]==32*28) || (centipede[h][y]==32*29) || (centipede[h][y]==32*30) || (centipede[h][y]==32*31) || (centipede[h][y]==32*32)))
		{
			centipede[h][y]-=32;
			centipede[h][y]-=32;
			centiFace[h]=!centiFace[h];
			centipedeHead[h][x]=centipede[h][x];
			centipedeHead[h][y]=centipede[h][y];
		}


		else if(centipede[h][x] == 960 &&  ((centipede[h][y]==32*28) || (centipede[h][y]==32*29) || (centipede[h][y]==32*30)  || (centipede[h][y]==32*31) || (centipede[h][y]==32*32) ))
			{
				centipede[h][y]-=32;
				centipede[h][y]-=32;
				centiFace[h]=!centiFace[h];
				centipedeHead[h][x]=centipede[h][x];
				centipedeHead[h][y]=centipede[h][y];
				centipedeHead[h][y]=centipede[h][y];
			}


		if(centiFace[h]==true)
		{
			centipede[h][x]+=32;
			centipedeHead[h][x]=centipede[h][x];
			centipedeHead[h][y]=centipede[h][y];			
		}

		centipedeHead[h][x]=centipede[h][x];
		centipedeHead[h][y]=centipede[h][y];
			
		if(centipede[h][y] > 32*24)
		{
			centipedeHead[h][x]=centipede[h][x];
			centipedeHead[h][y]=centipede[h][y];
		}

	
	}

}

void moveCentipedeLeft(float centipede[12][3], float centipedeHead[][3],float mushroom[][3], sf::Clock& centipedeClock, bool centiFace[], int randomStart, int* numMushroom, int mushroomShot[], int* Level, int*centiSpeed, float ExtraCentipedeHead[][3], bool centiHead[], int &killedHeads, bool &shouldMove, bool go[], int &badMushroom, int &extra, int &numMush, float scorp[], float spider[])
{

	if (centipedeClock.getElapsedTime().asMilliseconds() < *centiSpeed)
		return;

	centipedeClock.restart();

	for(int h=0; h<12; h++)
	{
		
		if(centiFace[h]==false )
		{
			centipede[h][x]-=32;
			centipedeHead[0][x]=centipede[0][x];
			centipedeHead[0][y]=centipede[0][y];	
		}

		for(int l=0; l<300; l++)
		{
			if(centiFace[h]==false)
			{
				if(centipede[h][x] == mushroom[l][x] && centipede[h][y] == mushroom[l][y] && mushroom[l][exists]==true)
				{
					centipede[h][y]+=32;
					centiFace[h]=!centiFace[h];
					centipedeHead[0][x]=centipede[0][x];
					centipedeHead[0][y]=centipede[0][y];
				}
			}
			
			if(centiFace[h]==true)
			{
				if(centipede[h][x] == mushroom[l][x]-32 && centipede[h][y] == mushroom[l][y] && mushroom[l][exists]==true)
				{
					centipede[h][y]+=32;
					//centiFace[h][1]=true;
					centiFace[h]=!centiFace[h];
					centipedeHead[0][x]=centipede[0][x];
					centipedeHead[0][y]=centipede[0][y];

				}
			}
		}

		if(centipede[h][x] == -64 && centipede[h][y] <= 32*24)
		{
			centipede[h][y]+=32;
			//centiFace[h][1]=true;
			centiFace[h]=!centiFace[h];
			centipedeHead[0][x]=centipede[0][x];
			centipedeHead[0][y]=centipede[0][y];
		}
		


		else if(centipede[h][x] == 960 && centipede[h][y]!= 0  && centipede[h][y]<=32*24)
			{
				centipede[h][y]+=32;
				//centiFace[h][1]=true;
				centiFace[h]=!centiFace[h];
				centipedeHead[0][x]=centipede[0][x];
				centipedeHead[0][y]=centipede[0][y];
			}

		else if(centipede[h][x] == -64 && ((centipede[h][y]==32*24) || (centipede[h][y]==32*25) || (centipede[h][y]==32*26) || (centipede[h][y]==32*27)))
		{
			centipede[h][y]+=32;
			centiFace[h]=!centiFace[h];
			centipedeHead[0][x]=centipede[0][x];
			centipedeHead[0][y]=centipede[0][y];
		}


		else if(centipede[h][x] == 960 && ((centipede[h][y]==32*24) || (centipede[h][y]==32*25) || (centipede[h][y]==32*26) || (centipede[h][y]==32*27)))
			{
				centipede[h][y]+=32;
				centiFace[h]=!centiFace[h];
				centipedeHead[0][x]=centipede[0][x];
				centipedeHead[0][y]=centipede[0][y];
				centipedeHead[0][y]=centipede[0][y];
			}

		else if(centipede[h][x] == -64 &&  ((centipede[h][y]==32*28) || (centipede[h][y]==32*29) || (centipede[h][y]==32*30) || (centipede[h][y]==32*31) || (centipede[h][y]==32*32)))
		{
			centipede[h][y]-=32;
			centipede[h][y]-=32;
			centiFace[h]=!centiFace[h];
			centipedeHead[0][x]=centipede[0][x];
			centipedeHead[0][y]=centipede[0][y];
		}


		else if(centipede[h][x] == 960 &&  ((centipede[h][y]==32*28) || (centipede[h][y]==32*29) || (centipede[h][y]==32*30)  || (centipede[h][y]==32*31) || (centipede[h][y]==32*32) ))
			{
				centipede[h][y]-=32;
				centipede[h][y]-=32;
				centiFace[h]=!centiFace[h];
				centipedeHead[0][x]=centipede[0][x];
				centipedeHead[0][y]=centipede[0][y];
				centipedeHead[0][y]=centipede[0][y];
			}


		if(centiFace[h]==true)
		{
			centipede[h][x]+=32;
			centipedeHead[0][x]=centipede[0][x];
			centipedeHead[0][y]=centipede[0][y];			
		}

		centipedeHead[h][x]=centipede[h][x];
		centipedeHead[h][y]=centipede[h][y];
			
		if(centipede[h][y] > 32*24)
		{
			centipedeHead[0][x]=centipede[0][x];
			centipedeHead[0][y]=centipede[0][y];
		}

	
	}


	for(int i=0; i<12; i++)
	{
		if(centipede[i][x]<(-320) || centipede[i][x]>32*35)
		{
			centipede[i][exists]=false;
		}
	}




	//number of centipede body parts that are false
	int pShotCenti = 0;

	for(int k=0; k<12; k++)
	{
		if(centipede[k][exists]==false && centipedeHead[k][exists]==false)
		{
			pShotCenti += 1;
		}
	}

	if(pShotCenti == 12 && shouldMove == false)
	{
		*Level += 1;
		*centiSpeed -= 10;
 	
 	LevelUp(centipede,centipedeHead,mushroom, centipedeClock, centiFace, numMushroom, mushroomShot, randomStart,killedHeads, shouldMove , go, ExtraCentipedeHead, badMushroom,extra, *Level, scorp, spider);
	}

	else if(pShotCenti==12 && shouldMove == true && killedHeads>=3)
	{
		*Level +=1;
		*centiSpeed -= 10;
 	
 	LevelUp(centipede,centipedeHead,mushroom, centipedeClock, centiFace, numMushroom, mushroomShot, randomStart , killedHeads, shouldMove,go, ExtraCentipedeHead, badMushroom, extra, *Level, scorp, spider);
	}



}


void drawSpider(sf::RenderWindow& window, float spider[], sf::Sprite& spiderSprite)
{
	if(spider[exists] == true )
	{
		spiderSprite.setPosition(spider[x], spider[y]);
		window.draw(spiderSprite);
	}

}

void moveSpider(float spider[3], sf::Clock& spiderClock)
{
	if (spiderClock.getElapsedTime().asMilliseconds() < 300)

		return;

	spiderClock.restart();

	if (spider[x] <= (32*6))
	{
		spider[y] -= 32;
		spider[x] += 32;
	}
	if (spider[x] > (32*6) && spider[x] <= (32*12))
	{
		spider[y] += 32;
		spider[x] += 32;
	}
	if (spider[x] > (32*12) && spider[x] <= (32*18))
	{
		spider[y] -= 32;
		spider[x] += 32;
	}
	if (spider[x] > (32*18) && spider[x] <= (32*24))
	{
		spider[y] += 32;
		spider[x] += 32;
	}
	if (spider[x] > (32*24) && spider[x] <= (32*30))
	{
		spider[y] -= 32;
		spider[x] += 32;
	}
	
	if (spider[x] > (32*30))
	{
		spider[y] = 928;
		spider[x] = 0;
		spider[exists]=true;
	}

	// if (spider[y] < (32*22))
	// {
	// 	spider[exists] = false;
	// }

	
	
}

void drawScorp(sf::RenderWindow& window, float scorp[], sf::Sprite& scorpSprite)
{
	if(scorp[exists] == true )
	{
		scorpSprite.setPosition(scorp[x], scorp[y]);
		window.draw(scorpSprite);
	}

}

void moveScorp(float scorp[3], sf::Clock& scorpClock)
{
	if (scorpClock.getElapsedTime().asMilliseconds() < 110)

		return;

	scorpClock.restart();


	if (scorp[x] >= (-32*6))
	{
		scorp[x] += 32;
	}

	if (scorp[x] >= (32*50))
	{
		scorp[y] = (rand()%30)*32;
		scorp[x] = -32*5;
		scorp[exists]=true;
	}

	
}


void splitCentipede(float centipede[12][3], float centipedeHead[][3], sf::Clock& centipedeClock, bool centiFace[],float bullet[3], int *extra,float mushroom[][3], int* score, int *badMushroom, int* choice)
{
	int z;
	for(int j=0 ;j<12; j++)
	{
		z=j;

	if(*choice<=2)
	{
		if(bullet[x] == centipede[j][x] && bullet[y]==centipede[j][y] && bullet[exists]==true && centipede[j][exists] == true)
		{
			 if(bullet[x] == centipedeHead[z][x] && bullet[y]==centipedeHead[z][y] && centipedeHead[z][exists] == true)
			{
			
				while(centipede[z][exists] == true)
				{
					centipede[z][exists] = false;
					centipedeHead[z][exists] = false;
					z++;
				}
				*score += 20;
				
			}
			if(centipede[j][exists]==true && centipedeHead[j][exists]==false )
			{
			*score += 10;
			}
			

			
		}

	}

	else if(*choice>2)
	{
		if(bullet[x] == centipede[j][x] && bullet[y]==centipede[j][y] && bullet[exists]==true && centipede[j][exists] == true)
		{
			 if(bullet[x] == centipedeHead[z][x] && bullet[y]==centipedeHead[z][y] && centipedeHead[z][exists] == true)
			{
					centipede[j][exists] = false;
					centipedeHead[j][exists] = false;
					centipedeHead[j+1][exists]=true;
			}

		}	



	}

		if(bullet[x] == centipede[j][x] && bullet[y]==centipede[j][y] && bullet[exists]==true && centipede[j][exists] == true && centipede[j][y]<=32*24)
		{
			*extra +=1;
			
			mushroom[*extra][x] = centipede[j][x];
			mushroom[*extra][y] = centipede[j][y];
			mushroom[*extra][exists] = true;
			centipede[j][exists] = false;
			centipedeHead[j][exists] = false;
			centipedeHead[j+1][exists] = true;

			bullet[exists] = false;

		}

		if(bullet[x] == centipede[j][x] && bullet[y]==centipede[j][y] && bullet[exists]==true && centipede[j][exists] == true  && centipede[j][y]>=32*24)
		{
			*badMushroom +=1;
			
			mushroom[*badMushroom][x] = centipede[j][x];
			mushroom[*badMushroom][y] = centipede[j][y];
			mushroom[*badMushroom][exists] = true;
			centipede[j][exists] = false;
			centipedeHead[j][exists] = false;
			centipedeHead[j+1][exists] = true;

			bullet[exists] = false;

		}


		if(centipedeHead[j][x] == bullet[x] && centipedeHead[j][y] == bullet[y] )
			{
				centipedeHead[j][exists]=false;
				centipede[j][exists]=false;
			}	




	}
}
	void drawFlee(sf::RenderWindow& window, float flee[], sf::Sprite& fleeSprite)
{
	if(flee[exists] == true )
	{
		fleeSprite.setPosition(flee[x], flee[y]);
		window.draw(fleeSprite);
	}

}


void moveFlee(float flee[3], sf::Clock& fleeClock, float mushroom[][3], int &countingFleeMush)
{
	if (fleeClock.getElapsedTime().asMilliseconds() <200)

		return;

	fleeClock.restart();

	flee[y] += 32;	

	if(((rand()%25)+1)==3)
	{
		mushroom[220+countingFleeMush][exists]=true;
		mushroom[220+countingFleeMush][x]=flee[x];
		mushroom[220+countingFleeMush][y]=flee[y];
		countingFleeMush++;	
	}

	if (flee[y] > 960)
	{

		flee[exists] = false;
		flee[x] = ((rand()%30)+1)*32;
		flee[y] = 0;
	}


}

void LevelUp( float centipede[12][3], float centipedeHead[][3],float mushroom[][3], sf::Clock& centipedeClock, bool centiFace[], int* numMushroom, int mushroomShot[], int &randomStart, int &killedHeads, bool &shouldMove , bool go[], float ExtraCentipedeHead[][3], int &badMushroom, int &extra, int &Level1, float scorp[], float spider[])
{


	int g=(rand()%10)*boxPixelsY;

	mushroom[0][x] = 32*15;
	mushroom[0][y] = 768 ;

	mushroom[1][x] = 32*12;
	mushroom[1][y] = 768 ;

	mushroom[2][x] = 32*22;
	mushroom[2][y] = 768 ;

	for(int p=3; p<300; p++)
	{
	 	mushroom[p][x] = ((rand()%29)*boxPixelsX)+32;
	 	mushroom[p][y] = ((rand()%27)*boxPixelsY)+32;
	}

	*numMushroom=0;

	*numMushroom = (((rand()%10)+1)+20)+(10*Level1);

	for(int p=0; p<*numMushroom; p++)
	{
		mushroom[p][exists] = true;
	}	



	for(int p=200; p<300; p++)
	{
		mushroom[p][exists] = false;
	}


	for( int h=0; h<12 ; h++)
	{
		centipede[h][exists] = false;
		centipedeHead[h][exists] = false;
	}
	for( int h=0; h<12-(Level1) ; h++)
	{
		centipede[h][x] = randomStart+(32*h);
		centipede[h][y] = 0;
		centipede[h][exists] = true;
	}

	
	for(int g=0; g<12; g++)
	{
		centipedeHead[g][x]=centipede[g][x];	
		centipedeHead[g][y]=centipede[g][y];
		centipedeHead[g][exists] = false;
	}
	
	for(int i=12-Level1+1; i<12; i++)
	{
		centipede[i][x]=32;
		centipede[i][y]=(rand()%15)*32;
		centipedeHead[i][exists]=true;
		centipedeHead[i][x]=32;
		centipedeHead[i][y]=centipede[i][y];

	}
	
	
	mushroomShot[300]={0};
	//Level1++;
	//setting all true 
	for(int i=0; i<12; i++)
	{
	go[i]=true;
	}

	//counts the number of extra heads killed

	killedHeads = 0;

	scorp[3] = {};

	scorp[x] = -32*5;
	
	scorp[y] = (rand()%20)*32;
	
	scorp[exists] = true;

	spider[3] = {};

	spider[x] = 0;
	
	spider[y] = 928;
	
	spider[exists] = true;



	for(int g=0; g<12; g++)
	{
		// if(g%2==0)
		// {
		// ExtraCentipedeHead[g][x]=928;
		// }
		// if(g%2==1)
		// {
		// ExtraCentipedeHead[g][x]=0;
		// }
		// ExtraCentipedeHead[g][y] = (rand()%10)*32;
		ExtraCentipedeHead[g][exists] = false;
		//ExtraCentipedeHead[0][exists] = true;
	}
	
	badMushroom = 250;
	extra = 200;
	// int badMushroom = 50;
	for(int m=0; m<12; m++)
	{
		centiFace[m]=false; 
	}

	
	centipedeHead[0][exists]=true;


} 




void moveExtraHeads(float centipede[][3], float centipedeHead[][3],float mushroom[][3], sf::Clock& ExtraCentipedeHeadClock, bool centiFace[], int randomStart, int* numMushroom, int mushroomShot[], int &Level, int*centiSpeed, float ExtraCentipedeHead[][3], bool centiHead[], bool go[], bool &shouldMove, int &killedHeads)
{


	if (ExtraCentipedeHeadClock.getElapsedTime().asMilliseconds() < (*centiSpeed)-5)
	{

		return;
	}


	ExtraCentipedeHeadClock.restart();


	if(centipede[8][y]>32*25)
	{
		shouldMove = true;
		//cout<<shouldMove<<endl;
	}


	for(int l=0; l<12; l++)
	{

		if(shouldMove == true)
		{
			ExtraCentipedeHead[0][exists]=true;
			ExtraCentipedeHead[0][x]=960;
			ExtraCentipedeHead[0][y]=32;
		}

	
		if(ExtraCentipedeHead[0][y]>32 && go[0] ==true)
		{
			ExtraCentipedeHead[1][exists]=true;
			ExtraCentipedeHead[1][x]=0;
			ExtraCentipedeHead[1][y]=32*6;
			go[0] = false;
		}

		if(ExtraCentipedeHead[1][y]>32*8 && go[1] ==true)
		{
			ExtraCentipedeHead[2][exists]=true;
			ExtraCentipedeHead[2][x]=960;
			ExtraCentipedeHead[2][y]=32*5;
			go[1] = false;
		}

		if(ExtraCentipedeHead[2][y]>32*9 && go[2] ==true)
		{
			ExtraCentipedeHead[3][exists]=true;
			ExtraCentipedeHead[3][x]=0;
			ExtraCentipedeHead[3][y]=32*12;
			go[2] = false;
		}

		if(ExtraCentipedeHead[3][y]>32*14 && go[3] ==true)
		{
			ExtraCentipedeHead[4][exists]=true;
			ExtraCentipedeHead[4][x]=960;
			ExtraCentipedeHead[4][y]=32*4;
			go[3] = false;
		}

		if(ExtraCentipedeHead[4][y]>32*8 && go[4] ==true)
		{
			ExtraCentipedeHead[5][exists]=true;
			ExtraCentipedeHead[5][x]=0;
			ExtraCentipedeHead[5][y]=32;
			go[4] = false;
		}

		if(centiHead[l]==false && ExtraCentipedeHead[l][exists]==true)
		{
			ExtraCentipedeHead[l][x]-=32;
		}
		




		for(int p=0; p<300; p++)
		{

			if(centiHead[l]==false)
			{
				if(mushroom[p][exists]==true)
				{
					if(ExtraCentipedeHead[l][x] == mushroom[p][x] && ExtraCentipedeHead[l][y] == mushroom[p][y] && mushroom[p][exists]==true)
					{	
						//cout<<"in left"<<endl;
						ExtraCentipedeHead[l][y]+=32;
						centiHead[l]=!centiHead[l];

					}
				}
			}
			
			if(centiHead[l]==true)
			{
				if(mushroom[p][exists]==true)
				{
					if(ExtraCentipedeHead[l][x] == mushroom[p][x]-32 && ExtraCentipedeHead[l][y] == mushroom[p][y] && mushroom[l][exists]==true)
					{
						//cout<<"in right"<<endl;
						ExtraCentipedeHead[l][y]+=32;
						centiHead[l]=!centiHead[l];

					}
				}
			}
		}

		if(ExtraCentipedeHead[l][x] == -32 && ExtraCentipedeHead[l][y] <= 32*24)
		{
			ExtraCentipedeHead[l][y]+=32;
			centiHead[l]=!centiHead[l];
			
		}
		


		else if(ExtraCentipedeHead[l][x] == 960 && ExtraCentipedeHead[l][y]!= 0  && ExtraCentipedeHead[l][y]<=32*24)
			{
				ExtraCentipedeHead[l][y]+=32;
				centiHead[l]=!centiHead[l];

			}

		else if(ExtraCentipedeHead[l][x] == -32 && ((ExtraCentipedeHead[l][y]==32*24) || (ExtraCentipedeHead[l][y]==32*25) || (ExtraCentipedeHead[l][y]==32*26) || (ExtraCentipedeHead[l][y]==32*27)))
			{
				ExtraCentipedeHead[l][y]+=32;
				centiHead[l]=!centiHead[l];
			
			}


		else if(ExtraCentipedeHead[l][x] == 960 && ((ExtraCentipedeHead[l][y]==32*24) || (ExtraCentipedeHead[l][y]==32*25) || (ExtraCentipedeHead[l][y]==32*26) || (ExtraCentipedeHead[l][y]==32*27)))
			{
				ExtraCentipedeHead[l][y]+=32;
				centiHead[l]=!centiHead[l];
				
			}

		else if(ExtraCentipedeHead[l][x] == -32 &&  ((ExtraCentipedeHead[l][y]==32*28) || (ExtraCentipedeHead[l][y]==32*29) || (ExtraCentipedeHead[l][y]==32*30) || (ExtraCentipedeHead[l][y]==32*31) || (ExtraCentipedeHead[l][y]==32*32)))
			{
				ExtraCentipedeHead[l][y]-=32;
				ExtraCentipedeHead[l][y]-=32;
				centiHead[l]=!centiHead[l];
			
			}


		else if(ExtraCentipedeHead[l][x] == 960 &&  ((ExtraCentipedeHead[l][y]==32*28) || (ExtraCentipedeHead[l][y]==32*29) || (ExtraCentipedeHead[l][y]==32*30) || (ExtraCentipedeHead[l][y]==32*31) || (ExtraCentipedeHead[l][y]==32*32) ))
			{
				ExtraCentipedeHead[l][y]-=32;
				ExtraCentipedeHead[l][y]-=32;
				centiHead[l]=!centiHead[l];
				
			}


		if(centiHead[l]==true && ExtraCentipedeHead[l][exists]==true)
		{
			ExtraCentipedeHead[l][x]+=32;
						
		}


	}

}






/*

Prompts from chatgpt

~how to use sleep function such that the space bar doesnt work until the bullet leave the screen in a game in sfml

~i have a picture of mushroom in whuch there are diiferent states of mushroom after each shot, i am using that pic in the game but only see the first state of that pic, how to acces others am using it like this mushroomSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

~how to insert the sprite from sprite sheet if the sheet has just one row


*/
