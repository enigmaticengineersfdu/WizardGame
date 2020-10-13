#include "commandmode.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <fstream>


enum class Command {
        INVALID = 0,
        RESUME,
        QUIT,
        SAVE,
        LOAD,
        HELP,
        CREDITS
};

//A static hashtable used to lookup commands by name. 
static const std::unordered_map<std::string, Command> command_table = {
        {"resume",  Command::RESUME},
        {"quit",    Command::QUIT},
        {"save",    Command::SAVE},
        {"load",    Command::LOAD},
        {"help",    Command::HELP},
        {"credits", Command::CREDITS}
};


const std::pair<Command, std::string> make_command(std::string &&raw_input) 
{
        /*Convert the input string into an input stringstream to allow cin 
        * like reading.
        */
        std::istringstream reader(raw_input);
        //This will store the raw representation of the command.
        std::string raw_command;
        //Read just the command from the reader.
        reader >> raw_command;
        /*convert the command to all lowercase letters to make commands case 
        * insensitive.
        */
        for (char &c : raw_command) {
                c = std::tolower(c);
        }
        /*Match the lowered string against the string representation of each 
        * valid command to determine which it is or if it is invalid.
        */
        Command command;
        try {
                command = command_table.at(raw_command);
        }
        catch(std::out_of_range e) {
                command = Command::INVALID;
        }
        /*Return the command along with its arguments.*/
        return std::pair(command, reader.str());
}

/*Purpose: To handle the quit command.
* Preconditions: None.
* Postconditions: The process terminates with exit code 0.
*/
void inline quit_handler() noexcept
{
        std::exit(0);
}

/*Purpose: Displays the help file.
* Preconditions: None.
* Postconditions: The help file or an error message is displayed.
*/
void help_handler() noexcept
{
        
        std::ifstream help_reader(gl::help_path);
        std::string help_buf;
        //If it can be opened the help file is read and printed.
        if (help_reader.is_open()) {
                //While the end of file hasn't been reached keep reading.
                while (help_reader >> help_buf);
                //The help text is printed
                std::cout << help_buf << std::flush;
        }
        //If the file can't be opened print an error message.
        else {
                std::cout << "Error displaying help.\n";
        }
}

/*Purpose: Displays the credits file.
* Preconditions: None.
* Postconditions: The credits file or an error message is displayed.
*/
void credits_handler() noexcept
{
        std::ifstream credits_reader(gl::credits_path);
        std::string credits_buf;
        //If it can be opened the help file is read and printed.
        if (credits_reader.is_open()) {
                //While the end of file hasn't been reached keep reading.
                while (credits_reader >> credits_buf);
                //The help text is printed.
                std::cout << credits_buf << std::flush;
        }
        //If the file can't be opened print an error message.
        else {
                std::cout << "Error displaying credits.\n";
        }
}

void gl::command_mode(const ent::GameState& gs) noexcept
{
        //Print the command mode header
        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
        std::cout << "Apostate Command Mode\n";
        /*Read and carry out commands.*/
        std::string read_buffer;
        //I/O loop for command mode
        std::cin.clear();
        while (true) {
                std::cout << '>' << std::flush;
                std::getline(std::cin, read_buffer);
                std::pair<Command, std::string> command = make_command(std::move(read_buffer));

                //Match the commands with their respective handlers
                switch (command.first)
                {
                case Command::RESUME:
                        //If the user opts to resume this function returns control to the game loop.
                        return;
                case Command::QUIT:
                        /*Quits the game. This function will eventually ask if 
                        the player wants to save.*/
                        quit_handler();
                        break;//this will never be reached but it is here to suppress a compiler warning.
                case Command::HELP:
                        /*Displays the help file.*/
                        help_handler();
                        break;
                case Command::CREDITS:
                        /*Displays the credits file.*/
                        credits_handler();
                        break;
                }
        }
}
