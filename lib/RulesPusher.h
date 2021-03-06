
#ifndef RULESPUSHER_H
#define	RULESPUSHER_H

#include <QString>
#include <QByteArray>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include "../model/FilterRule.h"
#include "Logger.h"
#include "Configuration.h"

using namespace std;

class RulesPusher {
public:
    static const char* NF_CHAIN_FORWARD;
    static const char* NF_CHAIN_OUTPUT;
    static const char* NF_CHAIN_INPUT;

    static const char* EB_OUTPUT_FILE;
    static const char* IP_OUTPUT_FILE;
    static const char* IP6_OUTPUT_FILE;

    static const char* EB_NEGATION;
    static const char* EB_MASK_DELIMITER;

    static const char* EB_COMMAND;
    static const char* EB_COMMAND_APPEND;
    static const char* EB_COMMAND_CHAIN;
    static const char* EB_COMMAND_INPUT_IFACE;
    static const char* EB_COMMAND_OUTPUT_IFACE;
    static const char* EB_COMMAND_SOURCE_ADDR;
    static const char* EB_COMMAND_DEST_ADDR;
    static const char* EB_COMMAND_PROTOCOL;
    static const char* EB_COMMAND_ACTION;

    static const char* EB_COMMAND_IP_SOURCE_ADDR;
    static const char* EB_COMMAND_IP_DEST_ADDR;
    static const char* EB_COMMAND_IP_PROTOCOL;

    static const char* EB_COMMAND_IP6_SOURCE_ADDR;
    static const char* EB_COMMAND_IP6_DEST_ADDR;
    static const char* EB_COMMAND_IP6_PROTOCOL;

    static const char* IP_NEGATION;
    static const char* IP_MASK_DELIMITER;

    static const char* IP_COMMAND;
    static const char* IP6_COMMAND;
    static const char* IP_COMMAND_APPEND;
    static const char* IP_COMMAND_CHAIN;
    static const char* IP_COMMAND_INPUT_IFACE;
    static const char* IP_COMMAND_OUTPUT_IFACE;
    static const char* IP_COMMAND_SOURCE_ADDR;
    static const char* IP_COMMAND_DEST_ADDR;
    static const char* IP_COMMAND_PROTOCOL;
    static const char* IP_COMMAND_ACTION;
    static const char* IP_COMMAND_COMMENT;
    
    static const char* BRIDGE_NF_CALL_IPTABLES_DISABLE;
    static const char* BRIDGE_NF_CALL_IP6TABLES_DISABLE;

    /**
     * Constructor with configuration parameter.
     * @param configuration application configuration contains default actions
     */
    RulesPusher(Configuration *configuration);
    virtual ~RulesPusher();

    /**
     * Write rules from given list to system kernel - Netfilter.
     * Now using output files and system call of command eb/iptables-restore.
     * @param rules ordered list of rules by priority.
     * @return true on success / false on fault
     */
    bool writeRules(QList<FilterRule> rules);

    /**
     * Get output for given list to system kernel - Netfilter ebtables part.
     * Using output files and system call of command ebtables-restore.
     * @param rules ordered list of rules by priority
     * @return output for ebtables-restore.
     */
    QString getEbOutput(QList<FilterRule> rules);

    /**
     * Get output for given list to system kernel - Netfilter iptables or ip6tables part.
     * Using output files and system call of command Xtables-restore.
     * @param rules ordered list of rules by priority
     * @param protocol type of ip protocol for output (IPv4 / IPv6)
     * @return output for Xtables-restore.
     */
    QString getIpOutput(QList<FilterRule> rules, QString protocol);

    void setLog(bool log);
private:
    /**
     * Make header of file for ebtables
     * @return header of file
     */
    QString ebFileHeader();

    /**
     * Make footer of file for ebtables.
     * @return footer of file
     */
    QString ebFileFooter();

    /**
     * Make header of file for iptables
     * @return header of file
     */
    QString ipFileHeader();

    /**
     * Make footer of file for iptables.
     * @return footer of file
     */
    QString ipFileFooter();

    /**
     * Print rule to string in a format used by ebtables-restore.
     * @param rule rule instance
     * @param chain chain used in output
     * @return rule specification printed into inline string
     */
    QString rule2EbString(FilterRule *rule, const char *chain);

    /**
     * Print rule to string in a format used by iptables-restore.
     * @param rule rule instance
     * @param chain chain used in output
     * @return rule specification printed into inline string
     */
    QString rule2IpString(FilterRule *rule, const char *chain);

    /**
     * Print rule value to string for ebtables.
     * @param command command
     * @param value value
     * @param negation if value is negatiated
     * @return value as a inline string
     */
    QString value2EbString(const char *command, QString value, bool negation);

    /**
     * Print rule value to string for iptables.
     * @param command command
     * @param value value
     * @param negation if value is negatiated
     * @return value as a inline string
     */
    QString value2IpString(const char *command, QString value, bool negation);

    /**
     * Print address value to a string for ebtables.
     * @param command command
     * @param value value
     * @param mask mask
     * @param negation if value is negatiated
     * @param maskSet if mask is set
     * @return  address value as a inline string
     */
    QString address2EbString(const char *command, QString value, QString mask, bool negation, bool maskSet);

    /**
     * Print address value to a string for iptables.
     * @param command command
     * @param value value
     * @param mask mask
     * @param negation if value is negatiated
     * @param maskSet if mask is set
     * @return  address value as a inline string
     */
    QString address2IpString(const char *command, QString value, QString mask, bool negation, bool maskSet);

    /** Output file stream for ebtables */
    ofstream ebFile;
    /** Output file stream for iptables */
    ofstream ipFile;
    /** Output file stream for ip6tables */
    ofstream ip6File;

    /** Application configuration with default actions */
    Configuration *configuration;

    /** log enable */
    bool log;

};

#endif	/* RULESPUSHER_H */

