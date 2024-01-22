#include "csvfilewriter.h"

CSVFileWriter::CSVFileWriter()
{
}

CSVFileWriter::CSVFileWriter(string fileName)
    : m_output(fileName)
{
}

CSVFileWriter::~CSVFileWriter()
{
    if (m_output.is_open()) {
        m_output.close();
    }
}

void CSVFileWriter::open(string fileName)
{
    if (m_output.is_open()) {
        m_output.close();
    }
    m_output.open(fileName);
}

void CSVFileWriter::close()
{
    if (m_output.is_open()) {
        m_output.close();
    }
}

void CSVFileWriter::writeLine(string text)
{
    m_output << (text + '\n').c_str();
}

void CSVFileWriter::write(string text)
{
    m_output << text;
}
