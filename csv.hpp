#pragma once

#ifndef _CSV
#define _CSV

#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <assert.h>

using namespace std;

class CSV
{

private:
    vector< vector<string> > data;

    string lTrim(const string& str);
    string rTrim(const string& str);
    string trim(const string& str);

    void handleChar(const char& ch, string& row, vector<string>& row_vec, bool& r);
    bool parseRow(const char* row, vector<string>& result);

public:
    bool readFromFile(const char* filename);
    bool readFromData(const char* str_data, int len);

    CSV();
    CSV(const char* filename);

    void clear();

    const char* getItem(int row, int col);
    vector <string> getRow(int row);

    template<class T>
    void copyItem(T& t, int row, int col)
    {
        const char* value = getItem(row, col);
        if (!value)
        {
            return;
        }

        string d = value;

        stringstream ss;
        ss << d;
        ss >> t;
    }

    long rowsNum();
    long colsNum();
};

CSV::CSV()
{
}

CSV::CSV(const char* filename)
{
    readFromFile(filename);
}

void CSV::clear()
{
    data.clear();
}

const char* CSV::getItem(int row, int col)
{
    if (row >= data.size())
    {
        return nullptr;
    }

    if (col >= data[row].size())
    {
        return nullptr;
    }

    return data[row][col].c_str();
}

long CSV::rowsNum()
{
    return data.size();
}

long CSV::colsNum()
{
    if (data.empty())
    {
        return 0;
    }
    return data[0].size();
}

bool CSV::readFromFile(const char* filename)
{
    clear();

    FILE* file;
    fopen_s(&file, filename, "r");
    if (!file)
        return false;

    char ch;

    /** ��һ���ַ��Ƿ�\\r */
    bool r = false;

    string row;
    vector<string> row_vec;

    int i = 0;

    while ((ch = fgetc(file)) != EOF)
    {
        if (i < 3)
        {
            if (ch == '\357' || ch == '\273' || ch == '\277')
            {
                // �����BOM��UTF8�ļ�
                i += 1;
                continue;
            }
            i += 1;
        }

        handleChar(ch, row, row_vec, r);
    }

    fclose(file);

    if (!row.empty())
    {
        // ���һ��
        parseRow(row.c_str(), row_vec);
        data.push_back(row_vec);
    }
    return true;
}


bool CSV::readFromData(const char* str_data, int len)
{
    clear();
    /** ��һ���ַ��Ƿ�\\r */
    bool r = false;

    string row;
    vector<string> row_vec;

    // long len = strlen(str_data);

    for (int i = 0; i < len; i++)
    {
        const char& ch = str_data[i];
        if (i < 3)
        {
            if (ch == '\357' || ch == '\273' || ch == '\277')
            {
                // �����BOM��UTF8�ļ�
                continue;
            }
        }

        handleChar(ch, row, row_vec, r);
    }

    if (!row.empty())
    {
        // ���һ��
        parseRow(row.c_str(), row_vec);
        data.push_back(row_vec);
    }
    return true;
}

void CSV::handleChar(const char& ch, string& row, vector<string>& row_vec, bool& r)
{
    if (ch == '\r')
    {
        r = true;
        // һ�еĽ���
        if (parseRow(row.c_str(), row_vec))
        {
            data.push_back(row_vec);
            row = "";
            row_vec.clear();
        }
    }
    else
    {
        if (ch == '\n')
        {
            if (!r)
            {
                // һ�еĽ���
                if (parseRow(row.c_str(), row_vec))
                {
                    data.push_back(row_vec);
                    row = "";
                    row_vec.clear();
                }
            }

        }
        else
        {
            row += ch;
        }
        r = false;
    }
}

bool CSV::parseRow(const char* row, vector<string>& result)
{
    string str_row = trim(row);
    row = str_row.c_str();

    string str = "";
    /** ˫���ſ�ʼ */
    bool quotes_begin = false;
    /** һ�ʼ�� */
    bool item_started = false;

    long len = strlen(row);
    auto isItemEnd = [&](int i) -> bool
    {
        if (i >= len)
        {
            return true;
        }
        if (row[i] == ',')
        {
            return true;
        }
        return false;
    };

    auto isQuotes = [&](int i) -> bool
    {
        if (i >= len)
        {
            return false;
        }
        if (row[i] == '"')
        {
            return true;
        }
        return false;
    };


    for (int i = 0; i < len; i++)
    {
        char ch = row[i];
        if (ch == ',' || ch == '\t')
        {
            if (quotes_begin)
            {
                // ��һ��Ŀ�ʼ�����ſ�ʼ�ģ����һ�û������������
                str += ch;
            }
            else
            {
                // һ��Ľ���
                result.push_back(str);
                str = "";
                item_started = false;
            }
        }
        else if (ch == '"')
        {
            // ˫����Ҫ������һ��Ŀ�ͷ�ͽ�β��Ҫ��������������һ����֣������Ǵ���ĸ�ʽ
            if (item_started)
            {
                bool item_end = false;
                if (quotes_begin)
                {
                    if (isItemEnd(i + 1))
                    {
                        quotes_begin = false;
                        i += 1;
                        // һ��Ľ���
                        result.push_back(str);
                        str = "";
                        item_started = false;
                        item_end = true;
                    }
                }

                if (!item_end)
                {
                    if (isQuotes(i + 1))
                    {
                        // ��������˫����
                        str += ch;
                        i += 1;
                    }
                    else
                    {
                        // ���Ϸ��ĸ�ʽ���������˫����Ӧ��ʹ��������������ʾ
                        printf("%s\n", row);
                        assert(0);
                    }
                }
            }
            else
            {
                quotes_begin = true;
                item_started = true;
            }
        }
        else
        {
            item_started = true;
            str += ch;
        }

    }

    if (item_started)
    {
        // ���һ��
        if (quotes_begin)
        {
            // û�н������ţ���ʽ����
            printf("%s\n", row);
            assert(0);
        }
        result.push_back(str);
    }

    return true;
}

string CSV::lTrim(const string& str)
{
    if (str.compare("") == 0)
    {
        return "";
    }
    return str.substr(str.find_first_not_of(" \n\r\t"));
}

string CSV::rTrim(const string& str)
{
    if (str.compare("") == 0)
    {
        return "";
    }
    return str.substr(0, str.find_last_not_of(" \n\r\t") + 1);
}

string CSV::trim(const string& str)
{
    return lTrim(rTrim(str));
}

vector <string> CSV::getRow(int row)
{
    if (row < data.size())
        return data[row];
    vector <string> s;
    return s;
}
#endif // CSV
