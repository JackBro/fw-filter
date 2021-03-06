
#ifndef RULEEDITWIDGET_H
#define	RULEEDITWIDGET_H

#include <QtGui/QTabWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>
#include <QtGui/QComboBox>
#include <QtGui/QTextEdit>
#include <QtGui/QRadioButton>
#include <QRegExpValidator>

#include "NegationComboBox.h"
#include "MaskLineEdit.h"
#include "../model/FilterRulesModel.h"
#include "../lib/NetInterfaces.h"
#include "../lib/OptionsLoader.h"
#include "../lib/RulesPusher.h"

class RuleEditWidget : public QTabWidget {
    Q_OBJECT

public:
    RuleEditWidget(QWidget *parent);
    virtual ~RuleEditWidget();

    /**
     * Setting rules list model for interaction with rules selector.
     * Signal sends index to slot and widget get rule from sended index.
     * @param model rules list model pointer
     */
    void setRulesModel(FilterRulesModel *model);

    /**
     * Public slot for saving rule from widget to rules model on
     * actually selected rule.
     * @param index inces of selected rule in list of rules
     * @return true on success / false on fault
     */
    bool ruleSave(QModelIndex index);

public slots:
    /**
     * Public slot for updating edit widget with actual selected rule.
     * @param index index of selected rule in list of rules
     */
    void ruleSelected(QModelIndex index);

private slots:
    /**
     * Enable or disable net layer options.
     * Depends on current net protocol and protocol negation options.
     */
    void netProtocolChanged();

    /**
     * Slot to call if rule is changed - edited by user.
     */
    void ruleChangedSlot();

    /**
     * Slot to call if type of packet choice has changed.
     */
    void packetsTypeChanged();

private:
    static const char* MAC_ADDRESS_REGEX;
    static const char* IPV4_ADDRESS_REGEX;
    static const char* IPV6_ADDRESS_REGEX;
    static const int NORMAL_OPTION_INDEX;
    static const int NEGATION_OPTION_INDEX;
    static const int TAB_GENERAL_INDEX;
    static const int TAB_LINK_INDEX;
    static const int TAB_NET_INDEX;

    /**
     * Setup widget with general settins
     */
    void setupGeneralWidget();

    /**
     * Setup widget with general settings
     */
    void setupEbWidget();

    /** 
     * Setup widget with net layer settings.
     */
    void setupIpWidget();

    /**
     * Create GUI select for negation.
     * @param parent parent of created combobox
     * @return pointer to created combobox
     */
    NegationComboBox *makeNegationSelect(QWidget *parent);

    /**
     * Change gui in case of packet type.
     * @param bridge true if type is bridged packet
     */
    void packetsTypeChange(bool bridge, QString protocol);

    /** List of rule actions */
    QStringList actions;

    /** List of system interfaces */
    QStringList interfaces;

    /** List of possible link protocols */
    QStringList ebProtocols;

    /** List of possible link protocols in non bridge mode */
    QStringList ebProtocolsNonBridge;

    /** List of possible net protocols */
    QStringList ipProtocols;

    /** IP address validator */
    QRegExpValidator *ipAddrValidator;

    /** Rules list model pointer */
    FilterRulesModel *rulesModel;

    /* Tabs */
    /** Tab with general information */
    QWidget *tabGeneral;
    /** Tab with filtering information about 3rd layer */
    QWidget *tabIp;
    /** Tab with filtering information about 2nd layer */
    QWidget *tabEb;

    /* General edits */
    QLineEdit *nameEdit;
    QLabel *numberLabel;
    QComboBox *actionSelect;
    QTextEdit *descriptionEdit;
    QRadioButton *bridgeChoice;
    QRadioButton *nonBridgeChoice;

    /* EB edits */
    NegationComboBox *macSourceNegSelect;
    QLineEdit *macSourceEdit;
    MaskLineEdit *macSourceMaskEdit;
    NegationComboBox *macDestNegSelect;
    QLineEdit *macDestEdit;
    MaskLineEdit *macDestMaskEdit;
    NegationComboBox *inInterfaceNegSelect;
    QComboBox *inInterfaceSelect;
    NegationComboBox *outInterfaceNegSelect;
    QComboBox *outInterfaceSelect;
    NegationComboBox *ebProtoNegSelect;
    QComboBox *ebProtoSelect;

    /* IP edits */
    NegationComboBox *ipSourceNegSelect;
    QLineEdit *ipSourceEdit;
    MaskLineEdit *ipSourceMaskEdit;
    NegationComboBox *ipDestNegSelect;
    QLineEdit *ipDestEdit;
    MaskLineEdit *ipDestMaskEdit;
    NegationComboBox *ipProtoNegSelect;
    QComboBox *ipProtoSelect;

signals:

    /**
     * Editing rule is changed by user editing.
     */
    void ruleChanged();

};

#endif	/* RULEEDITWIDGET_H */

