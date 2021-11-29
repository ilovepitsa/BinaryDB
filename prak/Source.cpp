#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>

const char* PathO = "Order.bin";
const char* PathE = "Edition.bin";
const char* PathC = "Customer.bin";
const char* PathT = "Typography.bin";


struct Order
{
	int OrderNumber;
	char Pasport[11];
	int count;
	int NumbTypog;
};

struct Edition
{
	int OrderNumber;
	char EditionCode[14];
	char Author[256];
	char Title[256];
	int Volume;
};

struct Customer
{
	char Pasport[11];
	char LastName[256];
	char FirstName[256];
	char MiddleName[256];
	char BirthDay[11];
};

struct Typography
{
	int NumbTypog;
	char AdressTyp[256];
	char NumberTel[256];
};

void drop_left(char* s, int n);

void Insert(std::vector<Order>& Orders, std::vector<Edition>& Editions, std::vector<Customer>& Customers, std::vector<Typography>& Typographies);

void Read(std::vector<Order>& Orders);

void Read(std::vector<Edition>& Editions);

void Read(std::vector<Customer>& Customers);

void Read(std::vector<Typography>& Typographies);

void newOrder(std::vector<Order>& Orders, std::vector<Edition>& Editions, std::vector<Customer>& Customers, std::vector<Typography>& Typographies);

void writeToFiles(std::vector<Order>& Orders, std::vector<Edition>& Editions, std::vector<Customer>& Customers, std::vector<Typography>& Typographies);

void showCustomerByPasport(std::vector<Customer>& Customers);

void showOrderByNumber(std::vector<Order>& Orders);

void showEditionByNumber(std::vector<Edition>& Editions);

void showTypographyByNumber(std::vector<Typography>& Typographies);


int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	std::vector<Order> Orders;
	std::vector<Edition> Editions;
	std::vector<Customer> Customers;
	std::vector<Typography> Typographies;
	const char* PathO = "Order.bin";
	const char* PathE = "Edition.bin";
	const char* PathC = "Customer.bin";
	const char* PathT = "Typography.bin";
	Insert(Orders, Editions, Customers, Typographies);
	int key = 0;
	while (key != 10)
	{
		for (int i = 0; i < 120; i++)
			std::cout << '_';
		std::cout << "\n1)Вывести данные о заказах\n2)Вывести информацию о заказе по номеру заказа\n3)Вывести данные об изданиях\n4)Вывести информацию о издании по номеру заказа\n5)Вывести данные о всех заказчиках\n6)Вывести данные о заказчике по паспорту\n7)Вывести данные о типографиях\n8)Вывести данные о типографии по ее номеру\n9)Ввести новый заказ\n10)Выйти из программы\n";
		std::cin >> key;

		switch (key)
		{
		case 1:
			Read(Orders);
			break;
		case 2:
			showOrderByNumber(Orders);
			break;
		case 3:
			Read(Editions);
			break;
		case 4:
			showEditionByNumber(Editions);
			break;
		case 5:
			Read(Customers);
			break;
		case 6:
			showCustomerByPasport(Customers);
			break;
		case 7:
			Read(Typographies);
			break;
		case 8:
			showTypographyByNumber(Typographies);
			break;
		case 9:
			newOrder(Orders, Editions, Customers, Typographies);
			writeToFiles(Orders, Editions, Customers, Typographies);
			break;
		case 10:
			break;
		default:
			std::cout << "\nНеправильный ввод\n";
			break;
		}
	}

}

void Insert(std::vector<Order>& Orders, std::vector<Edition>& Editions, std::vector<Customer>& Customers, std::vector<Typography>& Typographies)
{
	std::ifstream in("allData.txt");
	char* line = new char[256];
	int i = 0;
	Order tempO;
	Edition tempE;
	Customer tempC;
	Typography tempT;
	std::ifstream Ord(PathO);
	std::ifstream Cust(PathC, std::ios::binary);
	std::ifstream Edit(PathE, std::ios::binary);
	std::ifstream Typ(PathT, std::ios::binary);
	memset(line, '\0', 256);
	char* tempCh = new char[256];
	if (Ord.is_open() && Cust.is_open() && Edit.is_open() && Typ.is_open())
	{
		bool flagT = false;
		bool flagC = false;
		bool flagE = false;
		bool flagO = false;
		while (!flagT || !flagC || !flagE || !flagO)
		{
			if (Ord.getline(line, 256, '\n') && !flagO)
			{

				i = 0;
				while (line[i] != ' ')
				{
					i++;
				}

				strncpy(tempCh, line, i);
				tempO.OrderNumber = atoi(tempCh);
				drop_left(line, i + 1);
				i = 0;
				while (line[i] != ' ')
				{
					i++;
				}
				memset(tempO.Pasport, '\0', 11);
				strncpy(tempO.Pasport, line, i);
				drop_left(line, i + 1);
				i = 0;
				while (line[i] != ' ')
				{
					i++;
				}
				memset(tempCh, '\0', 256);
				strncpy(tempCh, line, i);
				tempO.count = atoi(tempCh);
				drop_left(line, i + 1);
				memset(tempCh, '\0', 256);
				strcpy(tempCh, line);
				tempO.NumbTypog = atoi(tempCh);
				Orders.push_back(tempO);
				memset(line, '\0', 256);
			}
			else
			{
				memset(line, '\0', 256);
				flagO = true;
			}

			if (Cust.getline(line, 256, '\n') && !flagC)
			{
				i = 0;
				while (line[i] != ' ')
				{
					i++;
				}
				memset(tempC.Pasport, '\0', 256);
				strncpy(tempC.Pasport, line, i);
				drop_left(line, i + 1);
				i = 0;
				while (line[i] != ' ')
					i++;
				memset(tempC.LastName, '\0', 256);
				strncpy(tempC.LastName, line, i);
				drop_left(line, i + 1);
				i = 0;
				while (line[i] != ' ')
					i++;
				memset(tempC.FirstName, '\0', 256);
				strncpy(tempC.FirstName, line, i);
				drop_left(line, i + 1);
				i = 0;
				while (line[i] != ' ')
					i++;
				memset(tempC.MiddleName, '\0', 256);
				strncpy(tempC.MiddleName, line, i);
				drop_left(line, i + 1);

				strcpy(tempC.BirthDay, line);
				Customers.push_back(tempC);
				memset(line, '\0', 256);
			}
			else
			{
				memset(line, '\0', 256);
				flagC = true;
			}
			memset(line, '\0', 256);
			if (Edit.getline(line, 256, '\n') && !flagE)
			{

				i = 0;
				while (line[i] != ' ') i++;
				memset(tempCh, '\0', 256);
				strncpy(tempCh, line, i);
				tempE.OrderNumber = atoi(tempCh);
				drop_left(line, i + 1);
				i = 0;
				while (line[i] != ' ') i++;
				memset(tempE.EditionCode, '\0', 256);
				strncpy(tempE.EditionCode, line, i);
				drop_left(line, i + 1);
				i = 0;
				while (line[i] != ' ') i++;
				memset(tempE.Author, '\0', 256);
				strncpy(tempE.Author, line, i);
				drop_left(line, i + 1);
				i = 0;
				while (line[i] != ' ') i++;
				memset(tempE.Title, '\0', 256);
				strncpy(tempE.Title, line, i);
				drop_left(line, i + 1);
				memset(tempCh, '\0', 256);
				strcpy(tempCh, line);
				tempE.Volume = atoi(tempCh);
				Editions.push_back(tempE);
				memset(line, '\0', 256);
			}
			else
			{
				memset(line, '\0', 256);
				flagE = true;
			}

			if (Typ.getline(line, 256, '\n') && !flagT)
			{
				i = 0;
				while (line[i] != ' ') i++;
				memset(tempCh, '\0', 256);
				strncpy(tempCh, line, i);
				tempT.NumbTypog = atoi(tempCh);
				drop_left(line, i + 1);
				i = 0;
				while (line[i] != ' ') i++;
				memset(tempT.AdressTyp, '\0', 256);
				strncpy(tempT.AdressTyp, line, i);
				drop_left(line, i + 1);
				memset(tempT.NumberTel, '\0', 256);
				strcpy(tempT.NumberTel, line);
				Typographies.push_back(tempT);
				memset(line, '\0', 256);
			}
			else
				flagT = true;
		}
	}



}
void Read(std::vector<Order>& Orders)
{
	std::cout << "\nДанные о заказах\n";
	int size = Orders.size();
	for (int i = 0; i < size; i++)
	{
		std::cout << std::setw(4) << Orders[i].OrderNumber << "  ";
		std::cout << std::setw(10) << Orders[i].Pasport << "  ";
		std::cout << std::setw(4) << Orders[i].count << "  ";
		std::cout << std::setw(4) << Orders[i].NumbTypog << "\n";
	}
}
void Read(std::vector<Edition>& Editions)
{
	setlocale(LC_ALL, "Russian");
	std::cout << "\nДанные о Изданиях\n";
	int size = Editions.size();
	for (int i = 0; i < size; i++)
	{
		std::cout << std::setw(5) << Editions[i].OrderNumber << "  ";
		std::cout << std::setw(5) << Editions[i].EditionCode << "  ";
		std::cout << std::setw(5) << Editions[i].Author << "  ";
		std::cout << std::setw(10) << Editions[i].Title << "  ";
		std::cout << std::setw(5) << Editions[i].Volume << "\n";
	}
}
void Read(std::vector<Customer>& Customers)
{
	setlocale(LC_ALL, "Russian");
	std::cout << "\nДанные о заказчиках\n";
	int size = Customers.size();
	for (int i = 0; i < size; i++)
	{
		std::cout << std::setw(11) << Customers[i].Pasport << " ";
		std::cout << std::setw(15) << Customers[i].LastName << " ";
		std::cout << std::setw(15) << Customers[i].FirstName << " ";
		std::cout << std::setw(15) << Customers[i].MiddleName << " ";
		std::cout << std::setw(11) << Customers[i].BirthDay << "\n";
	}
}
void Read(std::vector<Typography>& Typographies)
{
	std::cout << "\nДанные по типографиям\n";
	int size = Typographies.size();
	for (int i = 0; i < size; i++)
	{

		std::cout << std::setw(3) << Typographies[i].NumbTypog << " ";
		std::cout << Typographies[i].AdressTyp << " ";
		std::cout << Typographies[i].NumberTel << "\n";

	}
}


void drop_left(char* s, int n)
{
	char* s2 = s + n;
	while (*s2)
	{
		*s = *s2;
		++s;
		++s2;
	}
	*s = '\0';
}

void newOrder(std::vector<Order>& Orders, std::vector<Edition>& Editions, std::vector<Customer>& Customers, std::vector<Typography>& Typographies) {
	Order tempO;
	Edition tempE;
	Customer tempC;
	Typography tempT;
	bool flagT = false, flagC = false;
	memset(tempT.AdressTyp, '\0', 256);
	memset(tempT.NumberTel, '\0', 256);
	memset(tempC.LastName, '\0', 256);
	memset(tempC.FirstName, '\0', 256);
	memset(tempC.MiddleName, '\0', 256);
	memset(tempC.BirthDay, '\0', 11);
	memset(tempE.Author, '\0', 11);
	memset(tempE.Title, '\0', 11);
	tempO.OrderNumber = Orders[Orders.size() - 1].OrderNumber + 1;
	std::cout << "\nВведите следующие данные: Тираж\n";
	std::cin >> tempO.count;
	std::cout << "\nНомер Типографии\n";
	std::cin >> tempO.NumbTypog;
	for (int i = 0; i < Typographies.size(); i++)
	{
		if (tempO.NumbTypog == Typographies[i].NumbTypog)
		{
			flagT = true;
			break;
		}
	}
	if (!flagT)
	{
		tempT.NumbTypog = tempO.NumbTypog;
		std::cout << "\nАдрес типографии\n";
		std::cin >> tempT.AdressTyp;
		std::cout << "\nНомер телефона типографии\n";
		std::cin >> tempT.NumberTel;
	}
	std::cout << "\nКод Издательства\n";
	std::cin >> tempE.EditionCode;
	tempE.OrderNumber = tempO.OrderNumber;
	std::cout << "\nАвтор\n";
	std::cin >> tempE.Author;
	std::cout << "\nНазвание произведения\n";
	std::cin >> tempE.Title;
	std::cout << "\nОбъем в страницах\n";
	std::cin >> tempE.Volume;
	std::cout << "\nПаспорт Заказчика\n";
	std::cin >> tempO.Pasport;
	for (int i = 0; i < Customers.size(); i++)
	{
		if (strcmp(tempO.Pasport, Customers[i].Pasport) == 0)
		{
			flagC = true;
			break;
		}
	}
	if (!flagC)
	{
		strcpy(tempC.Pasport, tempO.Pasport);
		std::cout << "\nИмя Заказчика\n";
		std::cin >> tempC.LastName;
		std::cout << "\nФамилия Заказчика\n";
		std::cin >> tempC.FirstName;
		std::cout << "\nОтчество Заказчика\n";
		std::cin >> tempC.MiddleName;
		std::cout << "\nДень рождения Заказчика\n";
		std::cin >> tempC.BirthDay;
	}
	Orders.push_back(tempO);
	Customers.push_back(tempC);
	Editions.push_back(tempE);
	Typographies.push_back(tempT);
}

void writeToFiles(std::vector<Order>& Orders, std::vector<Edition>& Editions, std::vector<Customer>& Customers, std::vector<Typography>& Typographies)
{
	const char* PathO = "Order.bin";
	const char* PathE = "Edition.bin";
	const char* PathC = "Customer.bin";
	const char* PathT = "Typography.bin";
	std::ofstream FOrder(PathO, std::ios::binary | std::ios::trunc | std::ios::out);
	std::ofstream FEdition(PathE, std::ios::binary | std::ios::trunc | std::ios::out);
	std::ofstream FCustomer(PathC, std::ios::binary | std::ios::trunc | std::ios::out);
	std::ofstream FTypography(PathT, std::ios::binary | std::ios::trunc | std::ios::out);
	int size = Orders.size();
	for (int i = 0; i < size; i++)
	{
		FOrder << Orders[i].OrderNumber << " ";
		FOrder << Orders[i].Pasport << " ";
		FOrder << Orders[i].count << " ";
		FOrder << Orders[i].NumbTypog << "\n";
	}
	size = Editions.size();

	for (int i = 0; i < size; i++)
	{

		FEdition << Editions[i].OrderNumber << " ";
		FEdition << Editions[i].EditionCode << " ";
		FEdition << Editions[i].Author << " ";
		FEdition << Editions[i].Title << " ";
		FEdition << Editions[i].Volume << "\n";

	}
	size = Customers.size();
	bool flag = false;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (strcmp(Customers[i].Pasport, Customers[j].Pasport) == 0)
			{
				std::cout << Customers[i].Pasport << " " << Customers[j].Pasport << std::endl;
				std::cout << "zdes\n";
				flag = true;
			}
		}
		if (flag)
		{
			std::cout << "zdes1\n";
			flag = false;
			continue;
		}
		flag = false;
		FCustomer << Customers[i].Pasport << " ";
		FCustomer << Customers[i].LastName << " ";
		FCustomer << Customers[i].FirstName << " ";
		FCustomer << Customers[i].MiddleName << " ";
		FCustomer << Customers[i].BirthDay << "\n";
	}
	size = Typographies.size();
	flag = false;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (Typographies[i].NumbTypog == Typographies[j].NumbTypog)
			{
				flag = true;
			}
		}
		if (flag)
		{
			flag = false;
			continue;
		}
		flag = false;
		FTypography << Typographies[i].NumbTypog << " ";
		FTypography << Typographies[i].AdressTyp << " ";
		FTypography << Typographies[i].NumberTel << " ";
	}
	FOrder.close();
	FEdition.close();
	FCustomer.close();
	FTypography.close();
}
void showCustomerByPasport(std::vector<Customer>& Customers)
{
	std::cout << "\nВведите серию и номер паспорта без пробела\n";
	char* Pasport = new char[10];
	std::cin >> Pasport;
	bool flag = false;
	for (int i = 0; i < Customers.size(); i++)
	{
		if (strcmp(Pasport, Customers[i].Pasport) == 0)
		{
			std::cout << "ФИО заказчика: " << Customers[i].LastName << " " << Customers[i].FirstName << " " << Customers[i].MiddleName << std::endl;
			std::cout << "День рождения заказчика: " << Customers[i].BirthDay << std::endl;
			flag = true;
			break;
		}
	}
	if (!flag)
		std::cout << "\nТакого заказчика в базе нет\n";

}

void showOrderByNumber(std::vector<Order>& Orders)
{
	std::cout << "\nВведите номер заказа\n";
	int number;
	std::cin >> number;
	bool flag = false;
	for (int i = 0; i < Orders.size(); i++)
	{
		if (number == Orders[i].OrderNumber)
		{
			std::cout << "Тираж заказа: " << Orders[i].count;
			std::cout << "\nНомер типографии: " << Orders[i].NumbTypog;
			std::cout << "\nСерия и номер паспорта заказчика: " << Orders[i].Pasport;
			flag = true;
			break;
		}
	}
	if (!flag)
		std::cout << "\nТакого заказа в базе нет\n";
}
void showEditionByNumber(std::vector<Edition>& Editions)
{
	std::cout << "\nВведите номер заказа\n";
	int number;
	std::cin >> number;
	bool flag = false;
	for (int i = 0; i < Editions.size(); i++)
	{
		if (number == Editions[i].OrderNumber)
		{
			std::cout << "\nИмя автора: " << Editions[i].Author;
			std::cout << "\nКод издания: " << Editions[i].EditionCode;
			std::cout << "\nНазвание произведения: " << Editions[i].Title;
			std::cout << "\nОбъем: " << Editions[i].Volume << "\n";
			flag = true;
			break;
		}
	}
	if (!flag)
		std::cout << "\nТакого заказа в базе нет\n";
}
void showTypographyByNumber(std::vector<Typography>& Typographies)
{
	std::cout << "\nВведите номер типографии\n";
	int number;
	std::cin >> number;
	bool flag = false;
	for (int i = 0; i < Typographies.size(); i++)
	{
		if (number == Typographies[i].NumbTypog)
		{
			std::cout << "\nАдрес типографии: " << Typographies[i].AdressTyp;
			std::cout << "\nЕё номер телефона: " << Typographies[i].NumberTel << "\n";
			flag = true;
			break;
		}
	}
	if (!flag)
		std::cout << "\nТакого заказа в базе нет\n";
}
