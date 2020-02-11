#include "ShaderReader.h"

/// <summary>
/// Read from the shader file and return the data
/// </summary>
/// <param name="t_fileName">File name and extention</param>
std::string ShaderReader::readFile(const std::string t_fileName)
{
	std::ifstream inputFile; // Create the file pointer
	inputFile.open("Shaders//" + t_fileName); // Open the file

	if (inputFile.is_open()) // Check that the file has opened successfully
	{
		std::string fileContents; // String to hold the contents of the file
		std::string line; // Holds one line of data

		// Loop while getting lines add the contents string
		while (std::getline(inputFile, line))
		{
			bool commandChar = false;

			// Loop through each character in the current line
			for (char const& character : line)
			{
				if (character == '\\') // if the character is a command character
				{
					commandChar = true; // Command char to true
					continue; // Skip to next part, no need to add the slash
				}
				if (commandChar) // Check what command character it is and add it to the string
				{
					if (character == 'n')
					{
						fileContents += '\n';
					}
					if (character == 'r')
					{
						fileContents += '\r';
					}

					commandChar = false;
					continue;
				}

				fileContents += character; // Add the current character to the string
			}
		}

		inputFile.close(); // Close the file

		// Return the contents of the file
		return fileContents;
	}
	else
	{
		throw(std::exception{ "Could not open shader file." }); // Display an error if the file didn't open
	}
}