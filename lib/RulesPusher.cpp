
#include "RulesPusher.h"

const char* RulesPusher::NF_CHAIN_FORWARD = "FORWARD";
const char* RulesPusher::NF_CHAIN_INPUT = "INPUT";
const char* RulesPusher::NF_CHAIN_OUTPUT = "OUTPUT";

const char* RulesPusher::EB_OUTPUT_FILE = "data/ebfile";
const char* RulesPusher::EB_NEGATION = "!";
const char* RulesPusher::EB_MASK_DELIMITER = "/";

const char* RulesPusher::EB_COMMAND = "ebtables-restore < %1";
const char* RulesPusher::EB_COMMAND_APPEND = "-A";
const char* RulesPusher::EB_COMMAND_CHAIN = "";
const char* RulesPusher::EB_COMMAND_INPUT_IFACE = "-i";
const char* RulesPusher::EB_COMMAND_OUTPUT_IFACE = "-o";
const char* RulesPusher::EB_COMMAND_SOURCE_ADDR = "-s";
const char* RulesPusher::EB_COMMAND_DEST_ADDR = "-d";
const char* RulesPusher::EB_COMMAND_PROTOCOL = "-p";
const char* RulesPusher::EB_COMMAND_ACTION = "-j";

const char* RulesPusher::IP_OUTPUT_FILE = "data/ipfile";

const char* RulesPusher::IP_NEGATION = "!";
const char* RulesPusher::IP_MASK_DELIMITER = "/";

const char* RulesPusher::IP_COMMAND = "iptables-restore < %1";
const char* RulesPusher::IP_COMMAND_APPEND = "-A";
const char* RulesPusher::IP_COMMAND_CHAIN = "";
const char* RulesPusher::IP_COMMAND_INPUT_IFACE = "-i";
const char* RulesPusher::IP_COMMAND_OUTPUT_IFACE = "-o";
const char* RulesPusher::IP_COMMAND_SOURCE_ADDR = "-s";
const char* RulesPusher::IP_COMMAND_DEST_ADDR = "-d";
const char* RulesPusher::IP_COMMAND_PROTOCOL = "-p";
const char* RulesPusher::IP_COMMAND_ACTION = "-j";

RulesPusher::RulesPusher(Configuration *configuration) {
    this->configuration = configuration;
}

RulesPusher::~RulesPusher() {
}

bool RulesPusher::writeRules(QList<FilterRule> rules) {
    Logger::getInstance()->debug("Pushing rules to system");
    ebFile.open(EB_OUTPUT_FILE, fstream::out);
    ipFile.open(IP_OUTPUT_FILE, fstream::out);

    ebFile << this->ebFileHeader().toAscii().data();
    ipFile << this->ipFileHeader().toAscii().data();

    /* iterate each rule and write rules to files */
    FilterRule rule;

    foreach(rule, rules) {
        if (rule.isChainInput()) {
            ebFile << rule2EbString(&rule, RulesPusher::NF_CHAIN_INPUT).toAscii().data();
            ipFile << rule2IpString(&rule, RulesPusher::NF_CHAIN_INPUT).toAscii().data();
        }

        if (rule.isChainForward()) {
            ebFile << rule2EbString(&rule, RulesPusher::NF_CHAIN_FORWARD).toAscii().data();
            ipFile << rule2IpString(&rule, RulesPusher::NF_CHAIN_FORWARD).toAscii().data();
        }

        if (rule.isChainOutput()) {
            ebFile << rule2EbString(&rule, RulesPusher::NF_CHAIN_OUTPUT).toAscii().data();
            ipFile << rule2IpString(&rule, RulesPusher::NF_CHAIN_OUTPUT).toAscii().data();
        }
    }

    ebFile << this->ebFileFooter().toAscii().data();
    ipFile << this->ipFileFooter().toAscii().data();

    ebFile.close();
    ipFile.close();

    /* write to netfilter */
    int ebReturn = -1;
    int ipReturn = -1;
    ebReturn = system(QString(EB_COMMAND).arg(EB_OUTPUT_FILE).toAscii().data());
    ipReturn = system(QString(IP_COMMAND).arg(IP_OUTPUT_FILE).toAscii().data());

    /* control return state */
    if (ebReturn != 0 || ipReturn != 0) {

        Logger::getInstance()->debug("Rules pushing failed");
        return false;
    } else {

        /* remove files */
        //remove(EB_OUTPUT_FILE);
        //remove(IP_OUTPUT_FILE);
        Logger::getInstance()->debug("Rules successfully pushed");
        return true;
    }
}

QString RulesPusher::ebFileHeader() {
    QString header;
    header = QString::fromUtf8("# Generated by fw-filter\n");
    header.append(QString::fromUtf8("*filter\n"));
    header.append(QString::fromUtf8(":INPUT %1\n").arg(configuration->getInputAction()));
    header.append(QString::fromUtf8(":FORWARD %1\n").arg(configuration->getForwardAction()));
    header.append(QString::fromUtf8(":OUTPUT %1\n").arg(configuration->getOutputAction()));

    return header;
}

QString RulesPusher::ipFileHeader() {
    QString header;
    header = QString::fromUtf8("# Generated by fw-filter\n");
    header.append(QString::fromUtf8("*filter\n"));
    header.append(QString::fromUtf8(":INPUT %1 [0:0]\n").arg(configuration->getInputAction()));
    header.append(QString::fromUtf8(":FORWARD %1 [0:0]\n").arg(configuration->getForwardAction()));
    header.append(QString::fromUtf8(":OUTPUT %1 [0:0]\n").arg(configuration->getOutputAction()));

    return header;
}

QString RulesPusher::ipFileFooter() {
    QString footer;
    footer.append(QString::fromUtf8("COMMIT\n"));

    return footer;
}

QString RulesPusher::ebFileFooter() {
    QString footer;

    return footer;
}

QString RulesPusher::rule2EbString(FilterRule *rule, const char *chain) {
    QString out;

    /* append rule command */
    out.append(QString("%1 ").arg(RulesPusher::EB_COMMAND_APPEND));

    /* chain */
    out.append(QString("%1 %2 ").arg(RulesPusher::EB_COMMAND_CHAIN, chain));

    /* input interface if it is set */

    if (rule->getInInterface() != FilterRule::OPTION_VALUE_UNSPECIFIED) {
        out.append(value2EbString(RulesPusher::EB_COMMAND_INPUT_IFACE,
                rule->getInInterface(), rule->isInInterfaceNeg()));
    }

    /* output interface if it is set */
    if (rule->getOutInterface() != FilterRule::OPTION_VALUE_UNSPECIFIED) {
        out.append(value2EbString(RulesPusher::EB_COMMAND_OUTPUT_IFACE,
                rule->getOutInterface(), rule->isOutInterfaceNeg()));
    }

    /* link protocol */
    if (rule->getEbProtocol() != FilterRule::OPTION_VALUE_UNSPECIFIED) {
        out.append(value2EbString(RulesPusher::EB_COMMAND_PROTOCOL,
                rule->getEbProtocol(), rule->isEbProtocolNeg()));
    }

    /* source link address */
    if (!rule->getEbSource().isEmpty()) {
        out.append(address2EbString(RulesPusher::EB_COMMAND_SOURCE_ADDR,
                rule->getEbSource(), rule->getEbSourceMask(),
                rule->isEbSourceNeg(), !rule->getEbSourceMask().isEmpty()));
    }

    /* destination link address */
    if (!rule->getEbDest().isEmpty()) {
        out.append(address2EbString(RulesPusher::EB_COMMAND_DEST_ADDR,
                rule->getEbDest(), rule->getEbDestMask(),
                rule->isEbDestNeg(), !rule->getEbDestMask().isEmpty()));
    }

    /* action */
    if (!rule->getAction().isEmpty())
        out.append(QString("%1 %2 ").arg(RulesPusher::EB_COMMAND_ACTION, rule->getAction().toAscii().data()));

    /* log output withou line end */
    Logger::getInstance()->debug(QString::fromUtf8(
            "Pushing for ebtables: %1").arg(out).toAscii().data());

    /* finally line end */
    out.append(QString::fromUtf8("\n"));

    return out;
}

QString RulesPusher::value2EbString(const char *command, QString value, bool negation) {
    QString out;

    out.append(QString::fromUtf8(command));
    if (negation)
        out.append(QString::fromUtf8(" %1").arg(RulesPusher::EB_NEGATION));
    out.append(QString(" %1 ").arg(value));

    return out;
}

QString RulesPusher::address2EbString(const char *command, QString value, QString mask, bool negation, bool maskSet) {
    QString out;

    out.append(QString::fromUtf8(command));
    if (negation)
        out.append(QString::fromUtf8(" %1").arg(RulesPusher::EB_NEGATION));
    out.append(QString(" %1").arg(value));

    /* mask */
    if (maskSet) {
        out.append(QString::fromUtf8("%1%2").arg(RulesPusher::EB_MASK_DELIMITER, mask));
    }

    /* finally append space*/
    out.append(QString::fromUtf8(" "));

    return out;
}

QString RulesPusher::rule2IpString(FilterRule *rule, const char *chain) {
    QString out;

    /* append rule command */
    out.append(QString("%1 ").arg(RulesPusher::IP_COMMAND_APPEND));

    /* chain */
    out.append(QString("%1 %2 ").arg(RulesPusher::IP_COMMAND_CHAIN, chain));

    /* input interface if it is set */
    if (rule->getInInterface() != FilterRule::OPTION_VALUE_UNSPECIFIED) {
        out.append(value2IpString(RulesPusher::IP_COMMAND_INPUT_IFACE,
                rule->getInInterface(), rule->isInInterfaceNeg()));
    }

    /* output interface if it is set */
    if (rule->getOutInterface() != FilterRule::OPTION_VALUE_UNSPECIFIED) {
        out.append(value2IpString(RulesPusher::IP_COMMAND_OUTPUT_IFACE,
                rule->getOutInterface(), rule->isOutInterfaceNeg()));
    }

    /* protocol */
    if (rule->getIpProtocol() != FilterRule::OPTION_VALUE_UNSPECIFIED) {
        out.append(value2IpString(RulesPusher::IP_COMMAND_PROTOCOL,
                rule->getIpProtocol(), rule->isIpProtocolNeg()));
    }

    /* source net address */
    if (!rule->getIpSource().isEmpty()) {
        out.append(address2IpString(RulesPusher::IP_COMMAND_SOURCE_ADDR,
                rule->getIpSource(), QString::number(rule->getIpSourceMask()),
                rule->isIpSourceNeg(),
                rule->getIpSourceMask() != FilterRule::INT_VALUE_UNSPECIFIED));
    }

    /* destination net address */
    if (!rule->getIpDest().isEmpty()) {
        out.append(address2IpString(RulesPusher::IP_COMMAND_DEST_ADDR,
                rule->getIpDest(), QString::number(rule->getIpDestMask()),
                rule->isIpDestNeg(),
                rule->getIpDestMask() != FilterRule::INT_VALUE_UNSPECIFIED));
    }

    /* action */
    if (!rule->getAction().isEmpty())
        out.append(QString("%1 %2 ").arg(RulesPusher::IP_COMMAND_ACTION, rule->getAction().toAscii().data()));

    /* log output without line end */
    Logger::getInstance()->debug(QString::fromUtf8(
            "Pushing for iptables: %1").arg(out).toAscii().data());

    /* finally line end */
    out.append(QString::fromUtf8("\n"));

    return out;
}

QString RulesPusher::value2IpString(const char *command, QString value, bool negation) {
    QString out;

    if (negation)
        out.append(QString::fromUtf8("%1 ").arg(RulesPusher::IP_NEGATION));
    out.append(QString::fromUtf8("%1 %2 ").arg(command, value));

    return out;
}

QString RulesPusher::address2IpString(const char *command, QString value, QString mask, bool negation, bool maskSet) {

    QString out;

    if (negation)
        out.append(QString::fromUtf8("%1 ").arg(RulesPusher::IP_NEGATION));
    out.append(QString::fromUtf8(command));
    out.append(QString(" %1").arg(value));

    /* mask */
    if (maskSet) {
        out.append(QString::fromUtf8("%1%2").arg(RulesPusher::IP_MASK_DELIMITER, mask));
    }

    /* finally append space*/
    out.append(QString::fromUtf8(" "));

    return out;
}
