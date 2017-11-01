#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<cctype>
#include<cstdlib>
#include<ctime>


using namespace std;
//struct that contains the phrase ,guessesRequired, and has been used
struct Phrase
{
    string text;
    string :: size_type guessesRequired;
    bool isUsed = false;


};


//returns weather a charater is a letter
bool isLetter(char letter);
//return the string phrase in the form of - - -  -- dashes
string phraseWithBlanks(const string text, const string correctGuess);
//finds the amount of unique letters and returns that number
int uniqueLetterCount(const string text);

//load phrases from the txt file
int loadPhrasesFromFile(string file, Phrase phrase[],int length);

//displays an array of phrases
void printPhrase(Phrase phrase[],int length);

//swaps the two phrase indexs
void swap(Phrase phrase[],int index1 , int index2);

//finds the smalles value
int smallestValue(const Phrase phrase[], int length, int startIndex);

//performs the slection sort
void selectionSort(Phrase phrase[], int length);

//returns a string that has either dashes or letters and dashes for the phrase
string phraseWithBlanks(const string text, string correct,char guess);

//draws the gallows for the game based on how man where incorrect
void drawGallows(int missCount);

//return the proper phrase for the difficulty level that was
int getDifficultyLevel();

//determines if the pharse has been used before
int isUsed(Phrase phrase[],int range,int max , int min);

//run the game
void runGame(Phrase phrase[],int phraseCount);

//determine weather letter is inside
bool isInside(const string text, char letter);
//return random level number for the phrase
int getRandomLevel(Phrase phrase[],int length,int level);
int randomNumber(int min , int max);

int main()
{


    //file name is phrases.txt
    string file = "default.txt";
    const int LENGTH = 100;
    int phraseCount;//the count of phrase inside the file
    Phrase phrase[LENGTH];//declaring the the phrase inside the struct
    char guess; 
    phraseCount = loadPhrasesFromFile(file,phrase,LENGTH);

    //sorts the phrase by requeired guesses
    selectionSort(phrase,phraseCount);
    //run the game
    runGame(phrase,phraseCount);



    return 0;
}//end of main

//random number funcition

int randomNumber(int min , int max)
{
    int range = max - min + 1;

    return rand() % range - min;
}

int loadPhrasesFromFile(string file,Phrase phrase [],int length)
{
    int index =0;
    string line;
    ifstream in(file); //declare fstream in


    //if checks to make sure the file did open
    if(!in.is_open())
    {
        cout<<"The file did not open"<<endl;
        return 0;

    }


    // reads the line from the file and adds it to thr struct
    while(getline(in,line))
    {

        phrase[index].text = line;
        phrase[index].isUsed = false;
        phrase[index].guessesRequired = uniqueLetterCount(line);
        //increments the index
        ++index;
    }



    //closes out the file
    in.close();

    return index;

}//end loadPhrasesFromFile

void printPhrase(Phrase phrase[],int length)
{
    int index;

    for(index =0; index < length; ++index)
    {
        cout<<setw(50) << left << phrase[index].text<<" "

            << setw(3) << right << phrase[index].guessesRequired
            <<endl;
        //<<phrase[index].isUsed;
    }

}//end printPhrase

int uniqueLetterCount( const string text)
{
    string uniqueLetters;
    char lowercase;

    for (string::size_type index = 0; index < text.size(); index++)
    {
        //places the text to lowercase to determine if it is unique
        lowercase = tolower(text[index]);
        if (isalpha(lowercase) && uniqueLetters.find(lowercase) == string::npos)
        {
            //increments the unique letter count;
            uniqueLetters += lowercase;
        }
    }


    return uniqueLetters.size();

}

void swap(Phrase phrase[],int index1 , int index2)
{
    Phrase temp = phrase[index1];

    phrase[index1] = phrase[index2];
    phrase[index2] = temp;
}

int smallestValue(const Phrase phrase[], int length, int startIndex)
{
    int minIndex = startIndex;
    //for loop to run throught the phrase array
    for(int index = startIndex +1; index < length; ++index)
    {
        if(phrase[minIndex].guessesRequired > phrase[index].guessesRequired)
        {
            //makes the the minIndex the index
            minIndex = index;
        }
    }

    return minIndex;
}

void selectionSort(Phrase phrase[], int length)
{
    int minIndex;
    for(int firsIndexOfUnsorted = 0; firsIndexOfUnsorted < length;
        ++firsIndexOfUnsorted)
        {
            minIndex = smallestValue(phrase,length,firsIndexOfUnsorted);

            if(firsIndexOfUnsorted != minIndex)
            {
            swap(phrase,firsIndexOfUnsorted, minIndex);
            }
        }
}



void drawGallows(int missCount)
{
    // Output the top of the gallows
    cout
        << "   +----+     \n"
        << "   |    |     \n";


    // Output the stand and body
    switch (missCount)
    {
    case 0:
        cout
            << "   |       \n"
            << "   |       \n"
            << "   |       \n"
            << "   |       \n";
        break;

    case 1:
        cout
            << "   |    O  \n"
            << "   |    |  \n"
            << "   |       \n"
            << "   |       \n";
        break;

    case 2:
        cout
            << "   |    O  \n"
            << "   |   /|  \n"
            << "   |       \n"
            << "   |       \n";
        break;

    case 3:
        // The '\\' will output as '\', because it is a special char
        cout
            << "   |    O   \n"
            << "   |   /|\\ \n"
            << "   |        \n"
            << "   |        \n";
        break;

    case 4:
        cout
            << "   |    O   \n"
            << "   |   /|\\ \n"
            << "   |     \\ \n"
            << "   |        \n";
        break;

    default:
        cout
            << "   |    O    \n"
            << "   |   /|\\  \n"
            << "   |   / \\  \n"
            << "   |You're Dead\n";
    }


    // Output the base
    cout << "  =============\n" << endl;
}//end of the gallows

//is letter determines if input is a letter or not
bool isLetter(char letter)

{

      return isalpha(letter);

}

bool isInside(const string text, char letter)
{
    if(text.find(letter) != string::npos)
    {
        return true;

    }

    return false;
}


string phraseWithBlanks(const string text,string correct, char guess)
{
    //read the const phrase in

    string gameWord;


    //cout<<"Is this a letter? "<<isLetter(text[4])<<endl;
           for(string::size_type index =0; index < text.length(); ++index)

       {

             // if this is NOT a letter or it has been guessed, show it

             if(!isLetter(text[index]) || isInside(correct, tolower(text[index])))

             {

                   gameWord += text[index];

             }

             else // otherwise, show underscore

             {

                   gameWord += "_";

             }
       }



       return gameWord;


}

//is used function
int isUsed(Phrase phrase[],int range,int max, int min)
{
    /*
    int range = max - min + 1;
    return rand() % range - min;
*/
    unsigned int seed = static_cast<unsigned int>(time(NULL));

    srand(seed);


    int index;


    do{
        //check the range of random number

        index = rand() % range + min;
        phrase[index].isUsed;

    }while(phrase[index].isUsed != false);

    return index;
}
int getRandomLevel(Phrase phrase[],int length,int difficulty)
{
/*
    unsigned int seed = static_cast<unsigned int>(time(NULL));
    srand(seed);
*/
    int range = length/3;
    int min = range*(difficulty -1);
    int max = range *difficulty -1;


        switch(difficulty)
        {
            case 1:
            {


                return isUsed(phrase,range,max,min);




            }
            case 2:
            {


                return isUsed(phrase,range,max,min);

            }
            case 3:
            {


                return isUsed(phrase,range,max,min);


            }
            default:

                cout<<"There is an error"<<endl;

                return 0;

        }


}
//random number number
int getDifficultyLevel()
{
    int level;
    bool valid = false;
    while(valid != true)
    {
    cout<<"Difficulty level:"<<left<<endl;
    cout<<setw(10)<<"1)"<<setw(15)<<left<<"Easy"<<endl;
    cout<<setw(10)<<"2)"<<setw(15)<<left<<"Medium"<<endl;
    cout<<setw(10)<<"3)"<<setw(15)<<left<<"Hard"<<endl;
    cout<<"Pick difficulty (1 - 3): ";
    cin>>level;
        if(level <= 0 && level > 3)
        {
            cout<<"Please enter a number between 1 -3"<<endl;
            cin>>level;
            valid = false;
        }
        else{
            valid = true;
        }
    }

    return level;
}
//run game
void runGame(Phrase phrase[],int phraseCount)
{
    int missCount=0;
    char guess;
    string incorrectGuesses;
    string correctGuess;
    char answer;
    int guessCount;
    char lowerGuess;
    int unique;
    int correctCount=0;
    int level;

    do{
        int difficulty = getDifficultyLevel();
        level = getRandomLevel(phrase,phraseCount,difficulty);

            do
            {

                drawGallows(missCount);
                cout<<""<<endl;
                cout<<phraseWithBlanks(phrase[level].text,correctGuess,guess)
                <<endl;
                    //ask user for thier guess
                    cout<<"Previous incorrect guess: "<<incorrectGuesses<<endl;
                    cout<<" "<<endl;
                    cout<<"Please enter your guess: ";
                    cout<<" "<<endl;
                    cin>>guess;
                    lowerGuess = tolower(guess);
                        if(!isInside(phrase[level].text,lowerGuess) &&
                            !isInside(phrase[level].text,toupper(guess)))/*
                        if(isInside(phrase[level].text,lowerGuess) == false)*/
                        {
                            if(isInside(incorrectGuesses,lowerGuess) == false)
                            {
                            cout<<"Sorry "<<guess<<" is incorrect"<<endl;
                            ++missCount;
                            incorrectGuesses += guess;
                            }
                            else
                            {
                                cout<<"Oops you already guess wrong with this"
                                <<endl;
                            }
                        }
                        else
                        {

                                if(isInside(correctGuess,lowerGuess)== true)
                                {
                                    cout<<"Sorry but you have already used this"
                                    <<endl;
                                }
                                else
                                {
                                cout<<"Great you "<< guess<<" is correct"<<endl;
                                correctGuess+= guess;
                                ++correctCount;
                                }
                        }
                    cout<<endl;

                    cout<<endl;

                    //increments the guess count
                    ++guessCount;

                    //defines the number of uniqe charaters inside the puzzle
                    unique = uniqueLetterCount(phrase[level].text);

                    //determins if the puzzle is solved
                    if(correctCount == unique)
                    {
                        cout<<"Congraduations You WON!"<<endl;
                        //set the is used to phrase to true
                        phrase[level].isUsed = true;
                        //breaks after the puzzle is solved
                        break;
                    }
                    //displays the your dead gallowsif max incorrect guess are
                    //hit
                    if(missCount == 5)
                    {
                        //redraws gallows
                        drawGallows(5);
                        //makes the phrase unusabale.
                        phrase[level].isUsed = true;
                    }

                }while(missCount != 5 ||  guess<=unique);

        cout<<"Thanks For playing would you like to play again? (Y/N)"<<endl;
        cin>>answer;
        missCount = 0;
        incorrectGuesses = " ";
        correctCount = 0;
        correctGuess = " ";
    }while(tolower(answer) == 'y');

    cout<<"You did great, thank you for playing"<<endl;
}