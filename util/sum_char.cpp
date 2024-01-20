#include <iostream>
#include <cstring>

/*----------------------------| Read XML file |---------------------------*/
char* readXmlFile(const char* path) {
	FILE* file = fopen(path, "r");
	if (file == NULL) {
		std::cout << "File can't be opened.\n";
	}

	// Определение размера файла
    fseek(file, 0L, SEEK_END);  // Установка позиции в потоке данных
    long file_size = ftell(file);  // Опрос текущей позиции в потоке данных
    rewind(file);  // установка текущей позиции для чтения/записи в начало файла

    // Выделение памяти для буфера
    char* buffer = (char*)malloc(file_size + 1);

    if (buffer == NULL) {
        printf("Ошибка выделения памяти.\n");
        fclose(file);
    }

    // Чтение содержимого файла в буфер
    size_t read_size = fread(buffer, 1, file_size, file);

    if (read_size != file_size) {
        printf("Ошибка чтения файла.\n");
        fclose(file);
        free(buffer);
    }

    buffer[file_size] = '\0';  // Добавляем завершающий нулевой символ

    fclose(file);  // Закрываем файл
    return buffer;
}

/*-------------------------| Calculate ID |-------------------------------*/
int calculateWeatherId(const char* str) {
	int id = 0;
	for (int i = 0; str[i] != 0; i++) {
		id += str[i];
	}
	return id;
}

int calculateWeatherId(const std::string& str) {
	int id = 0;
	for (uint8_t i = 0; i < str.length(); i++)
		id += str[i];
	return id;
}

int main() {
	std::cout << "Start calculating..." << std::endl;
	const char* xml_example = readXmlFile("cbr-xml-daily.ru_daily_utf8.xml");
	const char* currencySubString = "<Value>";
	const char* result = NULL;
	result = strstr(xml_example, currencySubString);

	if (result != NULL) {
		std::cout << "Подстрока найдена: " << result - xml_example + 1<< '\n';
	} else {
		std::cout << "Подстрока не найдена.\n";
	}

	std::string sName = "ovc-ra";
	std::cout << sName << ": " << calculateWeatherId(sName);

	char usdCurrency[7] = {0};
	std::cout << '\n';
	result = result + strlen(currencySubString);
	for (int i = 0; i < 7; i++)
		usdCurrency[i] = *(result++);
	usdCurrency[7] = '\0';
	
	for (int i = 0; i < 7 != '\0'; i++) {
		if (usdCurrency[i] == ',')
			usdCurrency[i] = '.';
	}
	float fUsd = atof(usdCurrency);

	char eur_currency[7] = {0};

	result = strstr(result, currencySubString);

	result = result + strlen(currencySubString);

	for (int i = 0; i < 7; i++)
		eur_currency[i] = *(result++);
		
	eur_currency[7] = '\0';
	
	return EXIT_SUCCESS;
}