#pragma once
#ifndef DEP_TABLE
#define DEP_TABLE

/////////////////////////////////////////////////////////////////////
//	Project#2:			Type-based Dependency Analysis			   //
//					    To create a Type-based dependency analyzer //
//																   //
//	## Created by using Prof. Jim Fawcett's 'CodeAnalyzer'     ##  //
//  ## project and augmenting it with 'Type Analysis',         ##  //
//  ## 'Dependency Analysis' and 'Strong Components' features. ##  //
//																   //
//  Dep_Table.h:	   Header file to create Dependency Table	   //
//  *************************************************************  //
//	Version:		   1.0										   //
//  Date:			   03/15/2017								   //
//  Language:          Visual C++, Version 11.					   //
//  Platform:          Visual Studio Community Edition			   //
//					   HP ENVY, Windows 10				           //
//  Application:       CSE687 - Object Oriented Design             //
//  Author:            Sachin Basavani Shivashankara			   //
//	SUID:			   267871645								   //
//  Ph:, email:        (315)751-5895, sbasavan@syr.edu			   //
/////////////////////////////////////////////////////////////////////

// Module Operations:
// ==================
// Contains a class (DependencyTable) that saves and displays Dependency Table.
// 
// Public Interface:
// ==================
//			bool save(std::string typeName, DepInfo val);				// Save into Dependency Table
//			void display();												// Display Dependency Table
//			void displayHeader();										// Display Dependency Table Header
//			std::map<std::string, DepInfo>& returnDepTable();			// returns Dependency Table
//												 
// Required Files:
// ===============
// Dep_Table.h, Dep_Table.cpp

#include <iostream>
#include <string>
#include <vector>
#include <map> 
#include <iomanip> 
#include <sstream>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <exception>
#include <chrono>
#include <ctime>

#include "../Parser/Parser.h"
#include "../FileSystem/FileSystem.h"
#include "../FileMgr/FileMgr.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"
#include "../AbstractSyntaxTree/AbstrSynTree.h"
#include "../Logger/Logger.h"
#include "../Utilities/Utilities.h"
#include "../Analyzer/Executive.h"
#include"../Type_Table/Type_Table.h"
#include"../Type_Analysis/Type_Analysis.h"
#include "../Dependency_Analysis/Dep_Anal.h"
#include"../Type_Table/Type_Table.h"

namespace CodeAnalysis
{
	// Struct to store dependencies (vector of string)
	struct DepInfo
	{
		std::vector<std::string> DepItem ;
	};

	// Class to save and display Dependency Table
	class DependencyTable
	{
	private:
		std::map<std::string, DepInfo> DTmap;						// Dependency Table map
	public:
		bool save(std::string typeName, DepInfo val);				// Save into Dependency Table
		void display();												// Display Dependency Table
		void displayHeader();										// Display Dependency Table Header
		std::map<std::string, DepInfo>& returnDepTable();			// returns Dependency Table
	};

	// Returns Dependency Table
	inline std::map<std::string, DepInfo>& DependencyTable::returnDepTable()
	{
		return DTmap;
	}
	// Saves into Dependency Table
	inline bool DependencyTable::save(std::string typeName, DepInfo val)
	{
		for (auto v : val.DepItem) {
			DTmap[typeName].DepItem.push_back(v);
		}

		return true;
	}
	// Displays Dependency Header
	inline void DependencyTable::displayHeader()
	{
		std::cout << "\n";
		std::cout << std::right;
		std::cout << "\n" << "##########################################################################################";
		std::cout << "\n" << "                                 --DEPENDENCY TABLE--									   ";
		std::cout << "\n" << "##########################################################################################";
		std::cout << "\n ";
		std::cout << std::setw(25) << "File Name";
		std::cout << std::setw(25) << "Dependencies";
		std::cout << std::right;
		std::cout << "\n  ";
		std::cout << std::setw(25) << "-------------------";
		std::cout << std::setw(25) << "-------------------";
		
	}

	// Displays Dependency Table
	inline void DependencyTable::display()
	{
		DependencyTable::displayHeader();
		std::cout << "\n ";
		std::map<std::string, DepInfo>::iterator it = DTmap.begin();
		for (it; it != DTmap.end(); ++it)
		{
			std::cout << std::right;
			DepInfo val = it->second;
			for (std::string str : val.DepItem)
			{
				std::cout << std::setw(25) << it->first;
				std::cout << std::setw(25) << str;
				std::cout << "\n ";
			}
		}
	}
}
#endif