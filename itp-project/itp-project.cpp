#include <iostream>
#include <fstream> 
#include <sstream>
#include <string>
#include <limits> //to check whether input is correct or not (took this from the internet)
#include <conio.h> //to use _getch and clear the screen after user input

using namespace std;

const int maxTeams = 16;
const int maxPlayers = 176; //max number of players in the league (16 teams * 11 players per team)
const int maxPlayersPerTeam = 11;

class Player {
private:
	string residencyNumber;
	string firstName;
	string lastName;
	string birthDate;
	string phoneNumber;
	string teamName = "No Team";
	string position;
	double salary;

public:

	Player() {}; //default constructor that my code won't work without????
	Player(string residencyNumber, string firstName, string lastName, string birthDate, string phoneNumber, string position, double salary) { //constructor
		this->residencyNumber = residencyNumber;
		this->firstName = firstName;
		this->lastName = lastName;
		this->birthDate = birthDate;
		this->phoneNumber = phoneNumber;
		this->teamName = teamName;
		this->position = position;
		this->salary = salary;
	}

	//getters
	string getResidencyNumber() {
		return residencyNumber;
	}
	string getTeamName() {
		return teamName;
	}
	string getFirstName() {
		return firstName;
	}
	string getLastName() {
		return lastName;
	}
	string getBirthDate() {
		return birthDate;
	}
	string getPhoneNumber() {
		return phoneNumber;
	}
	string getPosition() {
		return position;
	}
	double getSalary() {
		return salary;
	}

	//setters
	void setPosition(string position) {
		this->position = position;
	}
	void setTeamName(string teamName) {
		this->teamName = teamName;
	}

	void displayPlayerInfo() {
		cout << "Residency number: " << residencyNumber << endl;
		cout << "First name: " << firstName << endl;
		cout << "Last name: " << lastName << endl;
		cout << "Birth date: " << birthDate << endl;
		cout << "Phone number: " << phoneNumber << endl;
		cout << "Team name: " << teamName << endl;
		cout << "Position: " << position << endl;
		cout << "Salary: " << salary << endl;
	}
};
class Team {
private:
	int teamNumber;
	string teamName;
	string teamAddress;
	string teamPhoneNumber;
	string teamCoachName;
	bool teamExists; //this is to check whether the team exists or not

	Player teamRoster[maxPlayersPerTeam]; //every team has an array of players
	int playerCount = 0; //this is to keep track of how many players are in a team

public:
	Team() : playerCount(0), teamExists(false) {} //default constructor

	Team(int teamNumber, string teamName, string teamAddress, string teamPhoneNumber, string teamCoachName) {
		this->teamNumber = teamNumber;
		this->teamName = teamName;
		this->teamAddress = teamAddress;
		this->teamPhoneNumber = teamPhoneNumber;
		this->teamCoachName = teamCoachName;
	}

	//list of getters
	int getTeamNumber() {
		return teamNumber;
	}
	string getTeamName() {
		return teamName;
	}
	string getTeamAddress() {
		return teamAddress;
	}
	string getTeamPhoneNumber() {
		return teamPhoneNumber;
	}
	string getTeamCoachName() {
		return teamCoachName;
	}
	Player* getTeamRoster() { //we used a pointer because we want to return the array of players
		return teamRoster;
	}
	int getPlayerCount() {
		return playerCount;
	}

	//methods to add and remove players from the roster
	void addPlayer(Player newPlayer) {
		if (playerCount < maxPlayersPerTeam) {
			teamRoster[playerCount] = newPlayer; //the new player is added to the team roster
			playerCount++;
		}
		else {
			cout << "The roster is full." << endl;
		}
	}
	void removePlayer(string playerResidencyNumber) {
		bool playerRemoved = false;

		//searches for the player in the roster
		for (int i = 0; i < playerCount; ++i) {
			if (teamRoster[i].getResidencyNumber() == playerResidencyNumber) {
				//move all players after the removed player one position to the left
				for (int j = i; j < playerCount - 1; ++j) {
					teamRoster[j] = teamRoster[j + 1];
				}
				playerCount--;
				playerRemoved = true;
				cout << "Player removed from the team." << endl;
				break;
			}
		}

		if (!playerRemoved) {
			cout << "Player not found in the team." << endl;
		}
	}

	//method to display the roster
	void displayTeamRoster() {
		if (playerCount == 0) { //if the roster is empty, the program will display a message, self explanatory
			cout << "Roster is empty." << endl;
			return;
		}

		cout << "Team Roster:" << endl;
		for (int i = 0; i < playerCount; ++i) { //loop through the roster to display all players
			cout << "Player " << i + 1 << ":" << endl;
			teamRoster[i].displayPlayerInfo();
			cout << endl;
		}
	}
};

Team teamList[maxTeams]; //an array of teams
Player playerList[maxPlayers]; //array of players

int teamCount = 0; //this is to keep track of how many teams there are
int playerCount = 0; //keep track of how many players there are


void writeTeamsToFile() {
	ofstream teamsFile("teams.txt");

	if (teamsFile.is_open()) {
		for (int i = 0; i < teamCount; ++i) { //goes through the teams and writes them to the file
			teamsFile << teamList[i].getTeamNumber() << ","
				<< teamList[i].getTeamName() << ","
				<< teamList[i].getTeamAddress() << ","
				<< teamList[i].getTeamPhoneNumber() << ","
				<< teamList[i].getTeamCoachName() << endl;
		}
		teamsFile.close();
		cout << "Teams data written to file successfully." << endl;
	}
	else {
		cout << "Unable to open teams file." << endl;
	}
}
void writePlayersToFile() {
	ofstream playersFile("players.txt");
	if (playersFile.is_open()) {
		for (int i = 0; i < playerCount; ++i) {
			playersFile << playerList[i].getResidencyNumber() << ","
				<< playerList[i].getFirstName() << ","
				<< playerList[i].getLastName() << ","
				<< playerList[i].getBirthDate() << ","
				<< playerList[i].getPhoneNumber() << ","
				<< playerList[i].getTeamName() << ","
				<< playerList[i].getPosition() << ","
				<< playerList[i].getSalary() << endl;
		}
		playersFile.close();
		cout << "Players data written to file successfully." << endl;
	}
	else {
		cout << "Unable to open players file." << endl;
	}
}
void readTeamsFromFile() {

	ifstream teamsFile("teams.txt");
	if (teamsFile.is_open()) {
		string line;
		while (getline(teamsFile, line)) {
			stringstream ss(line);
			string token;

			int teamNumber;
			string teamName, teamAddress, teamPhoneNumber, teamCoachName;

			getline(ss, token, ',');
			teamNumber = stoi(token);

			getline(ss, teamName, ',');
			getline(ss, teamAddress, ',');
			getline(ss, teamPhoneNumber, ',');
			getline(ss, teamCoachName, ',');

			Team newTeam(teamNumber, teamName, teamAddress, teamPhoneNumber, teamCoachName);
			teamList[teamCount] = newTeam;
			teamCount++;
		}
		teamsFile.close();
		cout << "Teams data read from file successfully." << endl;
	}
	else {
		cout << "Unable to open teams file." << endl;
	}
}
void readPlayersFromFile() {
	ifstream playersFile("players.txt");
	if (playersFile.is_open()) {
		string line;
		while (getline(playersFile, line)) {
			stringstream ss(line);
			string token;

			// Read player data separated by commas
			string residencyNumber, firstName, lastName, birthDate, phoneNumber, teamName, position;
			double salary;

			getline(ss, residencyNumber, ',');
			getline(ss, firstName, ',');
			getline(ss, lastName, ',');
			getline(ss, birthDate, ',');
			getline(ss, phoneNumber, ',');
			getline(ss, teamName, ',');
			getline(ss, position, ',');
			getline(ss, token, ','); // Read salary as a string
			salary = stod(token);    // Convert string to double

			Player newPlayer(residencyNumber, firstName, lastName, birthDate, phoneNumber, position, salary);
			playerList[playerCount] = newPlayer;
			playerCount++;
		}
		playersFile.close();
		cout << "Players data read from file successfully." << endl;
	}
	else {
		cout << "Unable to open players file." << endl;
	}
}

void createTeam() {
	int teamNumber;
	string teamName;
	string teamAddress;
	string teamPhoneNumber;
	string teamCoachName;
	do {
		cout << "Please insert team number: " << endl;
		cin >> teamNumber;
		if (cin.fail()) { //if the user inserts a letter, the program will prompt the user to enter a number
			cin.clear(); //clear the input
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the input
			cout << "Invalid input. Please enter a number." << endl;
			continue; //continue the loop
		}
	} while (cin.fail()); //loop until the user inserts an integer

	//user inserts team name, using getline because the team name can contain spaces
	cout << "Please insert team name: " << endl;
	cin.ignore();
	getline(cin, teamName);

	cout << "Please insert team address: " << endl; //same
	getline(cin, teamAddress);

	//user inserts team phone number, no letters, must be made of 11 digits
	do {
		cout << "Please insert team phone number: " << endl;
		cin >> teamPhoneNumber;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a number." << endl;
			continue;
		}
	} while (cin.fail()); //loop until the user inserts a number


	//user inserts team coach name, using getline *again* because the team coach name can contain spaces
	cout << "Please insert team coach name: " << endl;
	cin.ignore();
	getline(cin, teamCoachName);

	Team newTeam(teamNumber, teamName, teamAddress, teamPhoneNumber, teamCoachName); //new Team object

	if (teamCount < maxTeams) {
		teamList[teamCount] = newTeam;
		teamCount++;
		writeTeamsToFile(); //write the updated team data to the file
	}
	else {
		cout << "The league is full." << endl; //message for full league
	}
}
void deleteTeam() {
	int deleteTeamNumber;
	cout << "Enter the team number to delete: ";
	cin >> deleteTeamNumber;

	bool teamDeleted = false;
	for (int i = 0; i < teamCount; ++i) {
		if (teamList[i].getTeamNumber() == deleteTeamNumber) {
			teamList[i] = teamList[teamCount - 1];
			teamCount--;

			//update the files after deleting the team
			writeTeamsToFile();
			writePlayersToFile();

			cout << "Team successfully deleted." << endl;
			teamDeleted = true;
			break;
		}
	}

	if (!teamDeleted) {
		cout << "Team not found!" << endl;
	}
}
//function to check for residency number errors when creating player in case 8
void checkResidencyNumber(string residencyNumber) {
	if (residencyNumber.length() != 11) {
		cout << "Invalid residency number. Please enter a valid residency number." << endl;
		return;
	} //if the residency number is not 11 digits, the user will be prompted to enter it again

	bool isNumber = true; //bool to check if the string contains letters

	for (int i = 0; i < residencyNumber.length(); ++i) { //loop through the string to check if it contains letters
		if (!isdigit(residencyNumber[i])) { //if the string contains letters, the bool will be false
			isNumber = false;
			break;
		}
	}
	if (!isNumber) {
		cout << "Invalid residency number. Please enter a valid residency number." << endl;
		return;
	}
}
bool isValidResidencyNumber(const string& residencyNumber) {
	if (residencyNumber.length() != 11)
		return false;

	for (char digit : residencyNumber) {
		if (!isdigit(digit))
			return false;
	}

	return true;
}
void createPlayer() {
	//user inserts residency number, number has to be only 11 digits, no letters
	string residencyNumber;
	string firstName;
	string lastName;
	string birthDate;
	string phoneNumber;
	double salary;
	do {
		cout << "Please insert player's residency number: " << endl;
		cin >> residencyNumber;
		checkResidencyNumber(residencyNumber);
	} //if the residency number is not 11 digits or has letters, the user will be prompted to enter it again
	while (isValidResidencyNumber(residencyNumber) == false);

	cout << "Please insert player's first name: " << endl;
	cin >> firstName;

	cout << "Please insert player's last name: " << endl;
	cin >> lastName;

	//user inserts a dd/mm/yyyy date, must not contain letters and must be in the correct format and the date must be valid
	do {
		cout << "Please insert player's birth date (DD/MM/YYYY): " << endl;
		cin >> birthDate;
		if (cin.fail()) { //if the user inserts a letter, the program will prompt the user to enter a number
			cin.clear(); //clear the input
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the input
			cout << "Invalid input. Please enter a number." << endl;
			continue; //continue the loop
		}
	} while (cin.fail()); //loop until the user inserts a number
	if (birthDate.length() != 10) {
		cout << "Invalid date. Please enter a valid date." << endl;
		return;
	}
	if (birthDate[2] != '/' || birthDate[5] != '/') {
		cout << "Invalid date. Please enter a valid date." << endl;
		return;
	}
	//checks whether date is valid
	int day = stoi(birthDate.substr(0, 2));
	int month = stoi(birthDate.substr(3, 2));
	int year = stoi(birthDate.substr(6, 4));
	if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2020) {
		cout << "Invalid date. Please enter a valid date." << endl;
		return;
	}


	//user inserts phone number, no letters, must be made of 11 digits
	do {
		cout << "Please insert player's phone number: " << endl;
		cin >> phoneNumber;
		if (cin.fail()) { //if the user inserts a letter, the program will prompt the user to enter a number
			cin.clear(); //clear the input
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the input
			cout << "Invalid input. Please enter a number." << endl;
			continue; //continue the loop
		}
	} while (cin.fail()); //loop until the user inserts a number

	cout << "Please insert player's salary: " << endl;
	cin >> salary;

	Player newPlayer(residencyNumber, firstName, lastName, birthDate, phoneNumber, "No position yet", salary); //new player object

	if (playerCount < maxPlayers) {
		playerList[playerCount] = newPlayer;
		playerCount++;

		//write the updated player data to the file
		writePlayersToFile();

		cout << "Player added successfully." << endl;
	}
	else {
		cout << "The league is full." << endl;
	}
}
void listAllTeams() {
	cout << "List of all teams:" << endl;
	for (int i = 0; i < teamCount; ++i) {
		cout << "Team " << i + 1 << ":" << endl;
		cout << "Team number: " << teamList[i].getTeamNumber() << endl;
		cout << "Team name: " << teamList[i].getTeamName() << endl;
		cout << "Team address: " << teamList[i].getTeamAddress() << endl;
		cout << "Team phone number: " << teamList[i].getTeamPhoneNumber() << endl;
		cout << "Team coach name: " << teamList[i].getTeamCoachName() << endl;
		cout << "-----------------------" << endl;
	}
}

void clearScreen() {
	cout << "Press any key to continue...";
	_getch();
	system("cls");
}

int main()
{
	//read the information from files when the program starts
	readTeamsFromFile();
	readPlayersFromFile();

	int choice;

	cout << "\t\tWelcome to the football league manager" << endl; //title!
	do { //do while loop for the menu as long as the user doesn't exit...
		cout << "Team menu: " << endl;
		cout << "\t 1. Create a team" << endl;
		cout << "\t 2. Delete a team" << endl;
		cout << "\t 3. List all teams" << endl;
		cout << "\t 4. Add a player to a team" << endl;
		cout << "\t 5. Remove a player from a team" << endl;
		cout << "\t 6. List a team's roster" << endl;
		cout << "\t 7. Update a player's position" << endl;
		cout << "Player menu: " << endl;
		cout << "\t 8. Create a player" << endl;
		cout << "\t 9. Delete a player" << endl;
		cout << "\t 10. Update a player's information" << endl;
		cout << "\t 11. List all players and their information" << endl;
		cout << "\t 12. exit " << endl;
		cout << "Please enter your choice: " << endl;

		cin >> choice;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a number." << endl;
			continue;
		}
		//so that the program doesn't blow up if the user enters anything other than an integer

		//switch cases are the best for menu choices
		switch (choice) {
		case 1: {
			createTeam();
			cout << "Press any key to continue...";
			_getch();
			system("cls");
			break;
		}
		case 2: {
			if (teamCount == 0) {
				cout << "There are no teams available to delete." << endl;
				void clearScreen();
				break;
			}

			deleteTeam();
			void clearScreen();
			break;
		}
		case 3: {
			if (teamCount == 0) {
				cout << "There are no teams available." << endl;
				void clearScreen();
				break;
			}

			listAllTeams();
			void clearScreen();
			break;
		}
		case 4: {
			if (teamCount == 0) {
				cout << "There are no teams available. Please create a team first." << endl;
				void clearScreen();
				break;
			}

			cout << "Enter the team number to add a player: ";
			int selectedTeamNumber;
			cin >> selectedTeamNumber;

			bool teamFound = false;
			for (int i = 0; i < teamCount; ++i) {
				if (teamList[i].getTeamNumber() == selectedTeamNumber) {
					teamFound = true;

					cout << "Enter player's residency number to add: ";
					string playerResidencyNumber;
					cin >> playerResidencyNumber;

					bool playerFound = false;
					for (int j = 0; j < playerCount; ++j) {
						if (playerList[j].getResidencyNumber() == playerResidencyNumber) {
							playerFound = true;

							//user inserts the position of player
							string position;
							cin >> position;


							//add the player to the selected team with the provided position
							playerList[j].setPosition(position); //this assigns the position to that player
							teamList[i].addPlayer(playerList[j]); //this adds the player to the team

							cout << "Player added to team: " << teamList[i].getTeamName() << endl;

							//update files after adding the player to the team
							writeTeamsToFile();
							writePlayersToFile();

							void clearScreen();

							break;
						}
					}

					if (!playerFound) {
						cout << "Player not found!" << endl;
					}
					void clearScreen();
					break;
				}
			}

			if (!teamFound) {
				cout << "Team not found!" << endl;
			}
			void clearScreen();
			break;
		}
		case 5: {
			if (teamCount == 0) {
				cout << "There are no teams available. Please create a team first." << endl;
				break;
				void clearScreen();
			}

			cout << "Enter the team number to remove a player: ";
			int selectedTeamNumber;
			cin >> selectedTeamNumber;

			bool teamFound = false;
			for (int i = 0; i < teamCount; ++i) {
				if (teamList[i].getTeamNumber() == selectedTeamNumber) {
					teamFound = true;

					cout << "Enter player's residency number to remove: ";
					string playerResidencyNumber;
					cin >> playerResidencyNumber;

					//remove the player from the selected team
					teamList[i].removePlayer(playerResidencyNumber);

					//update the files after removing the player from the team
					writeTeamsToFile();
					writePlayersToFile();
					void clearScreen();
					break;
				}
			}

			if (!teamFound) {
				cout << "Team not found!" << endl;
			}
			void clearScreen();
			break;
		}
		case 6: {
			if (teamCount == 0) {
				cout << "There are no teams available. Please create a team first." << endl;
				void clearScreen();
				break;
			}

			cout << "Enter the team number to list its roster: ";
			int selectedTeamNumber;
			cin >> selectedTeamNumber;

			bool teamFound = false;
			for (int i = 0; i < teamCount; ++i) {
				if (teamList[i].getTeamNumber() == selectedTeamNumber) {
					teamFound = true;

					//display the roster of the selected team
					teamList[i].displayTeamRoster();
					void clearScreen();
					break;
				}
			}

			if (!teamFound) {
				cout << "Team not found!" << endl;
			}
			void clearScreen();
			break;
		}
		case 7: {
			cout << "Enter the player's residency number to update their position: ";
			string updateResidencyNumber;
			cin >> updateResidencyNumber;

			bool playerFound = false;
			for (int i = 0; i < playerCount; ++i) {
				if (playerList[i].getResidencyNumber() == updateResidencyNumber) {
					playerFound = true;

					//check if the player is in a team
					bool inTeam = false;
					for (int j = 0; j < teamCount; ++j) {
						for (int k = 0; k < teamList[j].getPlayerCount(); ++k) {
							if (teamList[j].getTeamRoster()[k].getResidencyNumber() == updateResidencyNumber) {
								inTeam = true;
								cout << "Player is in team: " << teamList[j].getTeamName() << endl;

								//update the player's position
								cout << "Enter new position for the player: ";
								string newPosition;
								cin >> newPosition;
								playerList[i].setPosition(newPosition);

								//update files after changing the player's position
								writeTeamsToFile();
								writePlayersToFile();

								cout << "Player's position updated in team " << teamList[j].getTeamName() << endl;
								void clearScreen();
								break;
							}
						}
					}

					if (!inTeam) {
						cout << "Player is not in any team." << endl;
						void clearScreen();
					}
					break;
				}
			}

			if (!playerFound) {
				cout << "Player not found!" << endl;
				void clearScreen();
			}
			break;
		}
		case 8: {
			createPlayer();
			void clearScreen();
			break;
		}
		case 9: {
			string deleteResidencyNumber;
			if (playerCount == 0) {
				cout << "There are no players available to delete." << endl;
				void clearScreen();
				break;
			}

			cout << "Enter the player's residency number to delete: ";
			cin >> deleteResidencyNumber;

			bool playerDeleted = false;
			for (int i = 0; i < playerCount; ++i) { //goes through all players
				if (playerList[i].getResidencyNumber() == deleteResidencyNumber) {

					for (int j = 0; j < teamCount; ++j) {
						teamList[j].removePlayer(deleteResidencyNumber); //removes the player from the team
					}

					playerList[i] = playerList[playerCount - 1]; //moves players after the deleted player one position to the left in the array

					playerCount--; //player deleted... counter's gonna go down obviously

					writePlayersToFile();

					cout << "Player successfully deleted." << endl;
					playerDeleted = true;
					void clearScreen();
					break;
				}
			}

			if (!playerDeleted) {
				cout << "Player not found!" << endl;
			}
			void clearScreen();
			break;
		}
		case 10: {
			if (playerCount == 0) { //if there are no players, the program will display a message, self explanatory
				cout << "There are no players available to update." << endl;
				void clearScreen();
				break;
			}
			string updateResidencyNumber;
			cout << "Enter the player's residency number to update their information: ";
			cin >> updateResidencyNumber;

			string residencyNumber;
			string firstName;
			string lastName;
			string birthDate;
			string phoneNumber;
			double salary;
			bool playerFound = false;

			for (int i = 0; i < playerCount; ++i) {
				if (playerList[i].getResidencyNumber() == updateResidencyNumber) {
					playerFound = true;

					do {
						cout << "Please insert player's residency number: " << endl;
						cin >> residencyNumber;
						checkResidencyNumber(residencyNumber);
					} //if the residency number is not 11 digits or has letters, the user will be prompted to enter it again
					while (isValidResidencyNumber(residencyNumber) == false);

					cout << "Please insert player's first name: " << endl;
					cin >> firstName;

					cout << "Please insert player's last name: " << endl;
					cin >> lastName;

					//user inserts a dd/mm/yyyy date, must not contain letters and must be in the correct format and the date must be valid
					do {
						cout << "Please insert player's birth date (DD/MM/YYYY): " << endl;
						cin >> birthDate;
						if (cin.fail()) { //if the user inserts a letter, the program will prompt the user to enter a number
							cin.clear(); //clear the input
							cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the input
							cout << "Invalid input. Please enter a number." << endl;
							continue; //continue the loop
						}
					} while (cin.fail()); //loop until the user inserts a number
					if (birthDate.length() != 10) {
						cout << "Invalid date. Please enter a valid date." << endl;

					}
					if (birthDate[2] != '/' || birthDate[5] != '/') {
						cout << "Invalid date. Please enter a valid date." << endl;

					}
					//checks whether date is valid
					int day = stoi(birthDate.substr(0, 2));
					int month = stoi(birthDate.substr(3, 2));
					int year = stoi(birthDate.substr(6, 4));
					if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2020) {
						cout << "Invalid date. Please enter a valid date." << endl;

					}


					//user inserts phone number, no letters, must be made of 11 digits
					do {
						cout << "Please insert player's phone number: " << endl;
						cin >> phoneNumber;
						if (cin.fail()) { //if the user inserts a letter, the program will prompt the user to enter a number
							cin.clear(); //clear the input
							cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignore the input
							cout << "Invalid input. Please enter a number." << endl;
							continue; //continue the loop
						}
					} while (cin.fail()); //loop until the user inserts a number

					cout << "Please insert player's salary: " << endl;
					double salary;
					cin >> salary;

					//update the player's information
					playerList[i] = Player(updateResidencyNumber, firstName, lastName, birthDate, phoneNumber, "", salary);

					//write the updated player data to the file
					writePlayersToFile();

					cout << "Player information updated." << endl;
					void clearScreen();
					break;
				}
			}

			if (!playerFound) {
				cout << "Player not found!" << endl;
			}
			void clearScreen();
			break;
		}
		case 11: {
			if (playerCount == 0) {
				cout << "There are no players available." << endl;
				void clearScreen();
				break;
			}

			cout << "List of all players:" << endl;
			for (int i = 0; i < playerCount; ++i) {
				if (i == 0)
					cout << "-----------------------" << endl; //to make the program look nicer

				cout << "Residency Number: " << playerList[i].getResidencyNumber() << endl;
				cout << "First Name: " << playerList[i].getFirstName() << endl;
				cout << "Last Name: " << playerList[i].getLastName() << endl;
				cout << "Birth Date: " << playerList[i].getBirthDate() << endl;
				cout << "Phone Number: " << playerList[i].getPhoneNumber() << endl;
				cout << "Team Name: " << playerList[i].getTeamName() << endl;
				cout << "Position: " << playerList[i].getPosition() << endl;
				cout << "Salary: " << playerList[i].getSalary() << endl;
				cout << "-----------------------" << endl;
			}
			void clearScreen();
			break;
		}
		case 12: {
			//instant exit
			break;
		}
		default: {
			cout << "Please enter a valid choice." << endl;
			void clearScreen();
			break;
		}
		}
	} while (choice != 12);			//exit when choice is 12

	system("cls");		//clear the screen after the user exits the program
	cout << "Thank you for using the football league manager" << endl;
	system("pause");
	return 0;
}