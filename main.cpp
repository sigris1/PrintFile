#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstring>
#include <cerrno>
#define ll long long

const char* kShortLinesArgument = "-l";
const char* kLongLinesArgument = "--lines=";
const char* kShortTailArgument = "-t";
const char* kLongTailArgument = "--tail";
const char* kShortDelimiterArgument = "-d";
const char* kLongDelimiterArgument = "--delimiter=";
const ll kLinesShift = 8;
const ll kDelimiterShift = 12;

struct Status {
    ll lines;
    ll tail;
    char delimiter;
    char* file_name;
};

bool IsNumeric(const char* str, ll q)
{
    for (ll i = q; i < strlen(str); ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

char IsChar(const char* str, char d, const char* next_str) {
    if (strncmp(str, kLongDelimiterArgument, kDelimiterShift) == 0) {
        if (str[kDelimiterShift] == '\\') {
            switch (str[kDelimiterShift + 1]) {
                case '0':
                    d = '\0';
                    return d;
                case 'a':
                    d = '\a';
                    return d;
                case 'b':
                    d = '\b';
                    return d;
                case 't':
                    d = '\t';
                    return d;
                case 'n':
                    d = '\n';
                    return d;
                case 'v':
                    d = '\v';
                    return d;
                case 'f':
                    d = '\f';
                    return d;
                case 'r':
                    d = '\r';
                    return d;
                default:
                    std::cout << "Incorrect d-data entered";
                    std::exit(EXIT_SUCCESS);
            }
        }
    } else {
        switch (next_str[1]) {
            case '0':
                d = '\0';
                return d;
            case 'a':
                d = '\a';
                return d;
            case 'b':
                d = '\b';
                return d;
            case 't':
                d = '\t';
                return d;
            case 'n':
                d = '\n';
                return d;
            case 'v':
                d = '\v';
                return d;
            case 'f':
                d = '\f';
                return d;
            case 'r':
                d = '\r';
                return d;
            default:
                std::cout << "Incorrect d-data entered";
                std::exit(EXIT_SUCCESS);
        }
    }
    return ' ';
}

void PrintFile(Status new_status) {
    char* file_name = new_status.file_name;
    ll lines = new_status.lines;
    ll tail = new_status.tail;
    char delimiter = new_status.delimiter;
    std::ifstream file;
    file.open(file_name);
    if (tail == 0) {
        for (int j = 0; j < lines; ++j) {
            char c;
            while (file >> std::noskipws >> c) {
                if (c != delimiter) {
                    std::cout << c;
                } else {
                    std::cout << c;
                    break;
                }
            }
        }
    }
    if (tail == 1) {
        ll check = 0;
        ll sum = 0;
        ll k = 0;
        char c;
        while (file >> std::noskipws >> c) {
            if (c == delimiter) {
                ++sum;
            }
        }
        ll delimiter_numbers[sum + 1];
        file.clear();
        file.seekg(0, std::ifstream::beg);
        ll delimiter_index = 1;
        delimiter_numbers[0] = 0;
        while (file >> std::noskipws >> c) {
            if (c == '\n') {
                ++check;
            }
            if (c == delimiter) {
                delimiter_numbers[delimiter_index] = k + 1 + check;
                ++delimiter_index;
            }
            ++k;
        }
        file.clear();
        file.seekg(delimiter_numbers[delimiter_index - lines], std::ifstream::beg);
        while (file >> std::noskipws >> c) {
            std::cout << c;
        }
    }
}

Status ParseArgs(int argc, char* argv[]){
    char * end;
    ll lines = 0;
    ll tail = 0;
    char delimiter = '\n';
    char* str;
    char* next_str;
    char* file_name;
    for (ll i = 1; i < argc; ++i) {
        str = argv[i];
        std::ifstream file(str);
        if (i < argc -1){
            next_str = argv[i + 1];
            int count = IsNumeric(next_str, 0);
            if (strcmp(str, kShortLinesArgument) == 0) {
                ++i;
                if (count == 1) {
                    lines = strtol(str + 8, &end, 10);
                    if (errno == ERANGE) {
                        std::cerr << "Out of range";
                        std::exit(EXIT_SUCCESS);
                    }
                } else {
                    std:: cerr << "Incorrect l-data entered";
                    std:: exit(EXIT_SUCCESS);
                }
            } else if (strcmp(str, kShortTailArgument) == 0 || strcmp(str, kLongTailArgument) == 0) {
                ++tail;
                if (tail > 1) {
                    std:: cerr << "Incorrect t-data entered";
                    std:: exit(EXIT_SUCCESS);
                }
            } else if (strcmp(str, kShortDelimiterArgument) == 0) {
                ++i;
                if (strlen(next_str) == 1) {
                    delimiter = next_str[0];
                } else if (strlen(next_str) == 2) {
                    delimiter = IsChar(next_str, delimiter, next_str);
                } else {
                    std:: cerr << "Incorrect d-data entered";
                    std:: exit(EXIT_SUCCESS);
                }
            } else if (strncmp(str, kLongLinesArgument, kLinesShift) == 0) {
                if (IsNumeric(str, kLinesShift) == 1) {
                    lines = strtol(str + kLinesShift, &end, 10);
                    if (errno == ERANGE) {
                        std::cerr << "Out of range";
                        std::exit(EXIT_SUCCESS);
                    }
                } else {
                    std:: cerr << "Incorrect l-data entered";
                    std:: exit(EXIT_SUCCESS);
                }
            }else if (strncmp(str, kLongDelimiterArgument, kDelimiterShift) == 0) {
                if (strlen(str + kDelimiterShift) == 1) {
                    delimiter = str[kDelimiterShift];
                } else if (strlen(str + kDelimiterShift) == 2) {
                    delimiter = IsChar(str, delimiter, next_str);
                } else {
                    std:: cerr << "Incorrect d-data entered";
                    std:: exit(EXIT_SUCCESS);
                }
            }
            else if (file.is_open() == 1){
                file_name = str;
            }
            else {
                std:: cerr << "Incorrect data entered";
                std:: exit(EXIT_SUCCESS);
            }
        } else {
            str = argv[argc - 1];
            if (strncmp(str, kLongDelimiterArgument, kDelimiterShift) == 0) {
                if (strlen(str + kDelimiterShift) == 1) {
                    delimiter = str[kDelimiterShift];
                } else if (strlen(str + kDelimiterShift) == 2) {
                    delimiter = IsChar(str, delimiter, next_str);
                } else {
                    std::cerr << "Incorrect d-data entered";
                    std::exit(EXIT_SUCCESS);
                }
            } else if (strncmp(str, kLongLinesArgument, kLinesShift) == 0) {
                if (IsNumeric(str, kLinesShift) == 1) {
                    lines = strtol(str + kLinesShift, &end, 10);
                    if (errno == ERANGE) {
                        std::cerr << "Out of range";
                        std::exit(EXIT_SUCCESS);
                    }
                } else {
                    std::cerr << "Incorrect l-data entered";
                    std::exit(EXIT_SUCCESS);
                }
            } else if (strcmp(str, kShortTailArgument) == 0 || strcmp(str, kLongTailArgument) == 0) {
                ++tail;
                if (tail > 1) {
                    std::cerr << "Incorrect t-data entered";
                    std::exit(EXIT_SUCCESS);
                }
            } else if (file.is_open() == 1) {
                file_name = str;
            } else {
                std::cerr << "Incorrect data entered";
                std::exit(EXIT_SUCCESS);
            }
        }
    }
    Status real_status {lines, tail, delimiter, file_name};
    return real_status;
}

int main(int argc, char* argv[]) {
    Status new_status = ParseArgs(argc, argv);
    PrintFile(new_status);
    return 0;
}