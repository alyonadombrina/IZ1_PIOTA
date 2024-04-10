//ЮФУ, ИКТИБ, МОП ЭВМ
//Программирование и основы теории алгоритмов часть 2
//Домашнее задание №1 -  ДКА
//КТбо1-6, Домбрина Алёна Игоревна
//Вариант 1.3
//24.03.24

#include <iostream>
#include <map>
#include <string>

using namespace std;

//Входные данные: введенная последовательность
//Функция valid_input проверяет вводимую последовательность на соответветствие входному алфавиту
//Если все элементы из алфавита {a, b} - функция возвращает true, если нет - false
bool valid_input(string);

//Входные данные: введенная последовательность итаблица переходов
//Функция output_of_transitions из исходного состояния q0 проходит по введенной последовательности и выводит состояния, 
//по которым проходит автомат.
//Если автомат останавливается в допускающем состоянии - функция возвращает true, в недопускающем - false
bool output_of_transitions(string , struct recognizer&);

//Структура recognizer содержит в себе поле table, которое представляет собой структуру данных, хранящую состояния и переходы по ним
//Структура данных основана на контейнере map, в котором ключ - состояние, элемент - map, 
//в котором ключ - символ, по которому мы переходим, элемент - состояние, в которое переходим.
struct recognizer
{
	map<string, map<char, string>> table =
	{
	{"q0" , { {'a', "q1" }, {'b', "q10"} } },
	{"q1" , { {'a', "q2" }, {'b', "q6"} } },
	{"q2" , { {'a', "q2" }, {'b', "q3"} } },
	{"q3" , { {'a', "q4" }, {'b', "q3"} } },
	{"q4" , { {'a', "q5" }, {'b', "q3"} } },
	{"q5" , { {'a', "q5" }, {'b', "q3"} } },
	{"q6" , { {'a', "q7" }, {'b', "q8"} } },
	{"q7" , { {'a', "q7" }, {'b', "q9"} } },
	{"q8" , { {'a', "q7" }, {'b', "q8"} } },
	{"q9" , { {'a', "q7" }, {'b', "q8"} } },
	{"q10" , { {'a', "q15" }, {'b', "q11"} } },
	{"q11" , { {'a', "q12" }, {'b', "q11"}  } },
	{"q12" , { {'a', "q12" }, {'b', "q13"} } },
	{"q13" , { {'a', "q12" }, {'b', "q14"} } },
	{"q14" , { {'a', "q12" }, {'b', "q14"} } },
	{"q15" , { {'a', "q17" }, {'b', "q16"} } },
	{"q16" , { {'a', "q18" }, {'b', "q16"} } },
	{"q17" , { {'a', "q17" }, {'b', "q16"} } },
	{"q18" , { {'a', "q17" }, {'b', "q16"} } }
	};
};
 
int main()
{
	setlocale(LC_ALL, "Russian");
	string sequence;
	
	do {
		cout << "Введите последовательность: ";
		choice:
		getline(cin, sequence);
		if (sequence == "exit")
		{
			cout << endl<<"Вы завершили работу! Спасибо за внимание!" << endl;
			break;

		}
		if (sequence.empty())
		{
			cout <<"Вы ввели пустую последовательность!" << endl;
			cout << endl << "Хотите продолжить работу?" << endl << "Если да - введите последовательность заново, если нет - введите exit: ";
			goto choice;
		}
		else if (!valid_input(sequence))
		{
			cout << "Вы использовали недопустимые символы!"<<endl;
			cout <<endl<< "Хотите продолжить работу?" << endl << "Если да - введите последовательность заново, если нет - введите exit: ";
			goto choice;
		}
		else if (sequence.size() < 2)
		{
			cout << "Вы ввели слишком короткую последовательность!"<<endl;
			cout << endl << "Хотите продолжить работу?" << endl << "Если да - введите последовательность заново, если нет - введите exit: ";
			goto choice;

		}
		else
		{
			recognizer automat;
			if(output_of_transitions(sequence, automat))
			{
				cout << "Yes" << endl;
				cout << "Введена допустимая последовательность!" << endl;
				cout << endl << "Хотите продолжить работу?" << endl << "Если да - введите последовательность заново, если нет - введите exit: ";
				goto choice;
			}
			else
			{
				cout << "No" << endl;
				cout << "Введена недопустимая последовательность!" << endl;
				cout << endl << "Хотите продолжить работу?" << endl << "Если да - введите последовательность заново, если нет - введите exit: ";
				goto choice;
			}
		}
		cout << endl;
	} while (true);

	return 0;
}


bool valid_input(string sequence)
{
	for (char c : sequence)
	{
		if (!strchr("ab", c))
		{
			return false;
		}
	}
	return true;
}

bool output_of_transitions(string sequence, struct recognizer& transition_table)
{
	string q_cur = "q0", q_follow;
	for (auto it = sequence.begin(); it != sequence.end(); it++)
	{
		q_follow = transition_table.table[q_cur][*it];
		cout << *it << ": " << q_cur << " -> " << q_follow << endl;
		q_cur = q_follow;
	}
	if (q_cur == "q2" || q_cur == "q5" || q_cur == "q6" || q_cur == "q9" || q_cur == "q11" || q_cur == "q14" || q_cur== "q15" || q_cur == "q18")
	{
		return true;
	}
	else
	{
		return false;
	}
}