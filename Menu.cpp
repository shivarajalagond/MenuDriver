#include<iostream>
#include "Menu.h"



//Default constructor intializes and allocates the option_list to 1
Menu::Menu()
{
	count = 0;
	max_list_size = 1;
	option_list = new Text[max_list_size];
	option_list[0].set(" ");
	top_prompt.set(" ");
	bottom_prompt.set(" ");
	top_text.set(" ");
	bottom_text.set(" ");
}

//copy constructor
Menu::Menu(const Menu &otherMenu)
{
	count = otherMenu.count;
	max_list_size = otherMenu.max_list_size;
	option_list = otherMenu.option_list;
	top_prompt = otherMenu.top_prompt;
	bottom_prompt = otherMenu.bottom_prompt;
	top_text = otherMenu.top_text;
	bottom_text = otherMenu.bottom_text;
}

//destructor to release the dynamic storage in use by optionlist
Menu::~Menu()
{
	delete[] option_list;
	option_list = 0;
}

//overloads the assignment operator
Menu & Menu::operator=(const Menu &otherMenu)
{
	if (this == &otherMenu) {
		return *this;
	}
	else {
		delete[] option_list;
		this->set_top_prompt(otherMenu.top_prompt);
		this->set_top_message(otherMenu.top_text);
		this->set_bottom_prompt(otherMenu.bottom_prompt);
		this->set_bottom_message(otherMenu.bottom_text);
		count = otherMenu.count;
		option_list = new Text[otherMenu.count];
		for (int i = 0; i < count; i++) {
			option_list[i] = otherMenu.option_list[i];
		}


	}
	return *this;
}

//doubles the capacity of option list
void Menu::double_capacity()
{
	max_list_size = max_list_size * 2;
}


//inserts new option to the existing list at given position 
//Also it validates the provied index if it is given range & current capacity of the option list
//Doubles the option list if the current capacity is full through double capacity function

void Menu::insert(int index, Text &option)
{

	if (index > 0) {

		if (size() == max_list_size - 1) {
			double_capacity();
			Text* temp = new Text[max_list_size];

			//To copy into temp from option_list
			for (int j = 0; j<size(); j++) {
				temp[j].set(option_list[j]);
			}

			//To shift the options by one position to right to insert the new option in option_list
			for (int i = index - 1; i<size(); i++) {
				temp[i + 1].set(option_list[i]);
			}

			//Option_list is insereted at the provided index or position
			temp[index - 1].set(option);

			//To make the option list to accomodate options including new option by deleting
			// old option list and making it to point to temp
			delete[] option_list;
			option_list = temp;
			//increasing the capacity by 1 to have the count of new inserted option list
			count = count + 1;
		}


		else {
			Text *temp = new Text[size() + 1];
			for (int j = 0; j<size(); j++) {
				temp[j].set(option_list[j]);
			}

			//Shift all the options to right by one position
			for (int i = index - 1; i<size(); i++) {
				temp[i + 1].set(option_list[i]);
			}

			//Option_list is insereted at the provided index or position
			temp[index - 1].set(option);

			//option list points to new optionlist
			delete[] option_list;
			option_list = temp;
			//increasing the capacity by 1 to have the count of new inserted option list
			count = count + 1;
		}
	}

	else {
		cout << "Please Enter valid Index " << endl;
	}

}

//First check the current capacity of option_list and doubles the capacity through double_capacity
//if there is no room to accomodate the new option
// Adds supplied option to the end of the option list

void Menu::push_back(char *option)
{

	if (size() == max_list_size) {
		double_capacity();
		Text* temp = new Text[max_list_size];
		for (int i = 0; i < size(); i++) {
			//int_to_string(i);
			temp[i].set(option_list[i]);
		}
		delete[] option_list;
		temp[count].set(option);
		option_list = temp;
		count = count + 1;
	}

	else {

		option_list[count].set(option);
		count = count + 1;
	}

}
//First check the current capacity of option_list and doubles the capacity through double_capacity
//if there is no room to accomodate the new option
// Adds supplied option to the end of the option list
void Menu::push_back(const Text &option)
{
	if (size() == max_list_size) {
		double_capacity();
		Text* temp = new Text[max_list_size];
		for (int i = 0; i < size(); i++) {
			temp[i].set(option_list[i]);
		}
		delete[] option_list;
		temp[count].set(option);
		option_list = temp;
		count = count + 1;
	}

	else {

		option_list[count].set(option);
		count = count + 1;
	}
}

//Function to remove an option from the list at the given index
Text Menu::remove(int index)
{
	Text removed;
	if (index >= 0 && index <= size()) {

		removed = option_list[index];
		option_list[index].set('\0');
		//count = count - 1;
		for (int i = index; i < size() - 1; i++) {
			option_list[i] = option_list[i + 1];
		}
		option_list[size() - 1].set('\0');
		count = count - 1;
	}

	else {
		cout << "Please Enter the index between [0-" << size() - 1 << "].";
	}

	return removed;
}

//returns the number of options in option list
int Menu::size() const
{
	return count;
}

//return the maximum number of options that the menu can support until it needs to expand
int Menu::capacity()
{
	return 0;
}

//Removes the last option in the list
void Menu::pop_back()
{
	
	//To set the last option to null
	option_list[count - 1].set('\0');

	//to decrease the count by 1 to have the proper count of options
	count = count - 1;

}

//returns the option at the index passed during function call
Text Menu::get(int index)
{
	Text retrived;
	if (index >= 0 && index <= size()) {
		retrived = option_list[index];
	}

	else {
		
		cout << "Index invalid" << "It must be in the range [1, " << size() << "]" << endl;
	}
	return retrived;
}

//returns a Text object storing the string representation of this menu
Text Menu::toString() const
{

	Text finalText;
	finalText.append(top_prompt);
	finalText.append("\n");
	finalText.append(top_text);
	finalText.append("\n");
	for (int i = 0; i <= size() - 1; i++)
	{
		finalText.append("(");
		finalText.append(finalText.int_to_string(i + 1));
		finalText.append(")");
		finalText.append(option_list[i]);
		finalText.append("\n");
	}
	finalText.append(bottom_text);
	finalText.append("\n");
	finalText.append("?->");
	finalText.append(bottom_prompt);

	return finalText;
}

//calls toString function to display the menu and takes the input and validates
//entered option number 

int Menu::read_option_number()
{
	int choice;
	cout << toString();
	cin >> choice;
	if (!isEmpty()) {
		while (!(choice >= 1 && choice <= size())) {

			cout << "Invalid choice " << choice << " .It must be in the range [1 ," << size() << "]" << endl;
			cout << "?->";
			cin >> choice;
		}

	}
	else {


	}
	return choice;
}
//sets top prompt to the supplied prompt
void Menu::set_top_prompt(const Text &prompt)
{
	top_prompt.set(prompt);
}
//sets bottom prompt to the supplied prompt
void Menu::set_bottom_prompt(const Text &prompt)
{
	bottom_prompt.set(prompt);
}

//sets opening Message
void Menu::set_top_message(const Text &message)
{
	top_text.set(message);
}

//sets closing message
void Menu::set_bottom_message(const Text &message)
{
	bottom_text.set(message);
}

//clears top prompt
void Menu::clear_top_prompt()
{
	top_prompt.set(" ");
}

//Removes bottom prompt
void Menu::clear_bottom_prompt()
{
	bottom_prompt.set(" ");
}

//Removes opening message
void Menu::clear_top_message()
{
	top_text.set(" ");
}

//clears closing message
void Menu::clear_bottom_message()
{
	bottom_text.set(" ");
}

//To check if the option is empty
bool Menu::isEmpty() const
{
	if (count>0) {
		return false;
	}

	else {
		return true;
	}
}


//overloads operator << operator and calls toString() function
ostream& operator<<(ostream& out, Menu& menu)
{
    out << menu.toString();
	return out;
}