#pragma once

#include "filedir.h"

class UI {
private:

public:
	std::string enter_path() {
		std::string path;
		std::cout << "������� ����:\n";
		std::cin >> path;
		return path;
	}

	std::string enter_filename() {
		std::string name;
		std::cout << "������� ��� �����:\n";
		std::cin >> name;
		return name;
	}

	int option() {
		int choice;
		std::cout << std::endl;
		std::cout << "�������� ��������:\n";
		std::cout << "1 - �������� ����������\n";
		std::cout << "2 - ������� ����/�����\n";
		std::cout << "3 - ������� ����/�����\n";
		std::cout << "4 - ������������� ����/�����\n";
		std::cout << "5 - �������� ������ �����\n";
		std::cout << "6 - ���������� ����� �� �����\n";
		std::cout << "7 - ������������� � ������ �����\n";
		std::cout << std::endl;
		std::cin >> choice;
		return choice;
	}

	void display_search(file& file, std::string mask) {
		std::vector<std::filesystem::path> tmp = file.search(mask);
		for (auto it = tmp.begin(), end = tmp.end(); it != end; it++) {
			std::cout << *it << " | " << it->filename() << std::endl;
		}
	}

	void show_content(dir& dir) {
		std::vector<std::filesystem::path> paths;
		if (std::filesystem::exists(dir.path) && std::filesystem::is_directory(dir.path))
		{
			for (auto const& entry : std::filesystem::directory_iterator(dir.path))
			{
				paths.emplace_back(entry.path());
			}
		}
	}

	int file_ot_dir() {
		int choice;
		std::cout << std::endl;
		std::cout << "�������� ��� ������������\n";
		std::cout << "1 - ����\n";
		std::cout << "2 - �����\n";
		std::cin >> choice;
		std::cout << std::endl;
		return choice;
	}
};

