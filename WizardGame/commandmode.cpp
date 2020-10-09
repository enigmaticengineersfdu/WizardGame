#include "commandmode.h"

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>


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

void command_mode(const ent::GameState& gs) noexcept
{
        //Print the command mode header
        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
        std::cout << "Apostate Command Mode\n";
        /*Read and carry out commands.*/
        std::string read_buffer;
        //I/O loop for command mode
        while (true) {
                std::cout << ">" << std::flush;
                std::getline(std::cin, read_buffer);
                std::pair command = make_command(std::move(read_buffer));
        }
}
