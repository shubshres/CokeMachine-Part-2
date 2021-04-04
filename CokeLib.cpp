// Coke Library
#include "CokeLib.h"

bool ParseCokeLine(const std::string& CokeMachineLine, std::vector<std::string>& params)
{
	int x = 0, z = 0, i = 0;

	if (CokeMachineLine.length() == 0)
	{
		return false;
	}
	else
	{
		while (z < CokeMachineLine.length())
		{
			x = CokeMachineLine.find("|", z) - z;
			params[i++] = CokeMachineLine.substr(z, x);
			z += params[i-1].length() + 1;
		}
	}
	return true;
}

void get_command_line_params(int argc, char *argv[], std::string& InputFileName, std::string& OutputFileName)
{
	int i;
	std::string cla;
	int ifilefound = 0, ofilefound = 0;
	
	for (i = 1; i < argc; i++)
	{
		cla = argv[i];

		if (cla.substr(0, cla.find("=")) == "INPUTFILENAME")
		{
			InputFileName = cla.substr(cla.find("=")+1, cla.length());
			ifilefound = 1;
		}
		else if (cla.substr(0, cla.find("=")) == "OUTPUTFILENAME")
		{
			OutputFileName = cla.substr(cla.find("=")+1, cla.length());
			ofilefound = 1;
		}
	}
	
	if (!(ifilefound && ofilefound))
	{
		throw std::invalid_argument("\nMissing command line parameters - Usage : INPUTFILENAME= OUTPUTFILENAME=\n");
	}
}