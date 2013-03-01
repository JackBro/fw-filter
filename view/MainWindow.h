
#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include <QtGui/QMessageBox>

#include "../qt/ui_MainWindow.h"
#include "RuleEditWidget.h"
#include "LogView.h"
#include "../lib/RulesPusher.h"
#include "../lib/RulesXML.h"
#include "../lib/Logger.h"
#include "../lib/Configuration.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow();
    virtual ~MainWindow();

    /**
     * Setter for list model of rules.
     * @param model rules list model
     */
    void setRulesViewModel(QAbstractItemModel *model);
    
    /**
     * Setter for configuration.
     * @param configuration configuration
     */
    void setConfiguration(Configuration *configuration);

private:
    Ui::MainWindow widget;
    
    /** Configuration */
    Configuration *configuration;
    
    /** Model of rules view */
    FilterRulesModel *rulesModel;

    /** Widget for rule editing */
    RuleEditWidget *ruleEditWidget;
    
    /** Log view */
    LogView *logView;

private slots:
    void on_newRuleButton_clicked();
    void on_deleteRuleButton_clicked();
    void on_duplicateRuleButton_clicked();
    void on_saveEditButton_clicked();
    void on_actionClose_triggered();
    void on_actionSave_rule_triggered();
    void on_actionNew_triggered();
    void on_actionDelete_triggered();
    void on_actionDuplicate_triggered();
    void on_actionApply_modifications_triggered();
    void on_actionReset_triggered();
    void on_actionSettings_triggered();

signals:

    /**
     * New rule at a given position
     * @param position position
     */
    void newRule(int position);

    /**
     * Delete rule from given position
     * @param position position
     */
    void deleteRule(int position);
    
    /**
     * Duplicate rule on given position
     * @param position position
     */
    void duplicateRule(int position);
    
    /**
     * Selected rule at given index.
     * Used in case of deleting rule. Deleted rule is not selected and
     * we must emit signal, that different rule is now selected.
     * @param index selected index
     */
    void selectedRule(QModelIndex index);
    
    void saveRule(QModelIndex index);

};

#endif	/* _MAINWINDOW_H */
