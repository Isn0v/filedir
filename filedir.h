#pragma once
#include <iostream>
#include <filesystem>
#include <fstream>
#include <Windows.h>
#include <vector>
#include "ui.h"





class basic_filedir
{
protected:
	std::string path; // "D:"
public:
	virtual void create(std::string _name) = 0;
	virtual void rename(std::string _oldname, std::string _newname) = 0;
	virtual void erase(std::string _name) = 0;
	virtual void copy(std::string _what, std::string _where) = 0;
	virtual void move(std::string _what, std::string _where) = 0;

	void reset_path(std::string _path) {
		path = _path;
	}

	inline void success() {
		std::cout << "Успех\n";
	}

	inline void error() {
		std::cout << "Ошибка\n";
	}

	void size(std::string what) {
		std::filesystem::path tmp(path + what);
		uintmax_t size = std::filesystem::file_size(tmp);
		if (size != 4096) {
			std::cout << std::endl;
			std::cout << tmp << " Размер: " << size << std::endl;
		}
		else {
			std::cout << "Файл слишком большой\n";
		}
	}

	friend class UI;
};

class file :public basic_filedir {
public:
	file(std::string _path){
		path = _path;
	}

	std::string CreateFilepath(std::string _name) {
		return path + _name;
	}

	
	
	void create(std::string _name) {
		std::string filepath = file::CreateFilepath(_name);
		std::ofstream out(filepath);
		if (out) {
			success();
		}
		else {
			error();
		}
	}

	void rename(std::string _oldname, std::string _newname) {
		std::string oldfilepath = file::CreateFilepath(_oldname);
		std::string newfilepath = file::CreateFilepath(_newname);
		int res = std::rename(oldfilepath.c_str(), newfilepath.c_str());
		if (res) {
			success();
		}
		else {
			error();
		}
	}

	void erase(std::string _name) {
		std::string filepath = file::CreateFilepath(_name);
		int res = std::remove(filepath.c_str());
		if (res) {
			success();
		}
		else {
			error();
		}
	}

	void copy(std::string _what, std::string _where) {
		std::string _oldfilepath = file::CreateFilepath(_what);
		std::string _newfilepath = _where + _what;
		std::ifstream in(_oldfilepath);
		std::ofstream out(_newfilepath);
		out << in.rdbuf();
	}

	void move(std::string _what, std::string _where) {
		std::string _oldfilepath = file::CreateFilepath(_what);
		std::string _newfilepath = _where + _what;
		std::ifstream in(_oldfilepath);
		std::ofstream out(_newfilepath);
		out << in.rdbuf();
		file::erase(_what);
	}

	std::vector<std::filesystem::path> search(std::string what)
	{
		std::vector<std::filesystem::path> paths;
		if (std::filesystem::exists(path) && std::filesystem::is_directory(path))
		{
			for (auto const& entry : std::filesystem::recursive_directory_iterator(path))
			{
				if (std::filesystem::is_regular_file(entry) && entry.path().filename() == what)
					paths.emplace_back(entry.path());
			}
		}
		else {
			error();
		}
		return paths;
	}

	friend class UI;
};

class dir : public basic_filedir {
public:
	dir(std::string _path) {
		path = _path;
	}

	std::string CreateDirectoryname(std::string _name) {
		return path + _name;
	}

	void create(std::string _name) {
		std::string directory_path = dir::CreateDirectoryname(_name);
		int res = std::filesystem::create_directory(directory_path);
		if (res) {
			success();
		}
		else {
			error();
		}
	}

	void rename(std::string _oldname, std::string _newname) {
		std::string old_dirpath = dir::CreateDirectoryname(_oldname);
		std::string new_dirpath = dir::CreateDirectoryname(_newname);
		try {
			std::filesystem::rename(old_dirpath, new_dirpath);
			success();
		}
		catch (std::runtime_error) {
			error();
		}
	}

	void erase(std::string _name) {
		std::string dir_name = dir::CreateDirectoryname(_name);
		try {
			std::filesystem::remove(dir_name);
			success();
		}
		catch (std::runtime_error) {
			error();
		}
	}


	void copy(std::string _what, std::string _where) {
		std::string old_dirpath = dir::CreateDirectoryname(_what);
		std::string new_dirpath = _where
			+ _what;
		try {
			std::filesystem::copy(old_dirpath,new_dirpath);
			success();
		}
		catch (std::runtime_error) {
			error();
		}
	}

	void move(std::string _what, std::string _where) {
		std::string old_dirpath = dir::CreateDirectoryname(_what);
		std::string new_dirpath = _where + _what;
		try {
			std::filesystem::copy(old_dirpath, new_dirpath);
			std::filesystem::remove(old_dirpath);
			success();
		}
		catch (std::runtime_error) {
			error();
		}
	}

	friend class UI;
};





