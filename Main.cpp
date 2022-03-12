#include <iostream>
#include "ui.h"

using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	UI work;
	cout << "Добро пожаловать в файловый менеджер!\n";
	string path = work.enter_path();

	file f(path);
	dir d(path);

	while (1) {
		int main_choice = work.option(), sub_choice;

		switch (main_choice) {
		case 1:
		{
			cout << endl;
			work.show_content(d);
			cout << endl;
		}
		break;
		case 2:
		{
			cout << endl;
			sub_choice = work.file_ot_dir() - 1;
			string what = work.enter_filename();
			if (!sub_choice) {
				f.create(what);
			}
			else {
				d.create(what);
			}
			cout << endl;
		}
		break;
		case 3:
		{
			cout << endl;
			sub_choice = work.file_ot_dir() - 1;
			string what = work.enter_filename();
			if (!sub_choice) {
				f.erase(what);
			}
			else {
				d.erase(what);
			}
			cout << endl;
		}
		break;
		case 4:
		{
			cout << endl;
			sub_choice = work.file_ot_dir() - 1;
			cout << "Что переименовать: \n";
			string old_name = work.enter_filename();
			cout << "Во что переименовать: \n";
			string new_name = work.enter_filename();
			if (!sub_choice) {
				f.rename(old_name, new_name);
			}
			else {
				d.rename(old_name, new_name);
			}
			cout << endl;
		}
		break;
		case 5:
		{
			cout << endl;
			string what = work.enter_filename();
			f.size(what);
			cout << endl;
		}
		break;
		case 6:
		{
			cout << endl;
			std::string mask;
			cout << "Введите маску поиска: ";
			cin >> mask;
			work.display_search(f, mask);
			cout << endl;
		}
		break;
		case 7:
		{
			cout << endl;
			string new_path = work.enter_path();
			f.reset_path(new_path);
			d.reset_path(new_path);
			cout << endl;
		}
		break;
		default:
			cout << endl;
			cout << "Ошибка" << endl;
		}

	return EXIT_SUCCESS;
}