
#include <QString>
#include <QByteArray>

#include "RulesPusher.h"

RulesPusher::RulesPusher() {
}

RulesPusher::~RulesPusher() {
}

bool RulesPusher::writeRules(QList<FilterRule> rules) {
    ebFile.open(EB_OUTUP_FILE);
    ebFile << this->ebFileHeader().toAscii().data();
    ebFile.close();
    
    return true;
}

QString RulesPusher::ebFileHeader() {
    QString header;
    header = QString::fromUtf8("# Generated by fw-filter\n");
    header.append(QString::fromUtf8("*filter\n"));
    header.append(QString::fromUtf8(":INPUT ACCEPT\n"));
    header.append(QString::fromUtf8(":FORWARD ACCEPT\n"));
    header.append(QString::fromUtf8(":OUTPUT ACCEPT\n"));
    
    return header;
}
