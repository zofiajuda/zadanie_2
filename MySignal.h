#ifndef SIGNAL_H
#define SIGNAL_H
#include <TObject.h>
#include <TH1.h>
#include <TCanvas.h>

class MySignal : public TObject
{

private:
    double t0_var;
    double tot_var;
    double charge_var;
    double amplitude_var;
    double baseline_var;

public:
    MySignal();
    MySignal(double t0_initial, double tot_initial, double charge_initial, double amplitude_initial, double baseline_initial);
    virtual ~MySignal();
    // functions returning variables
    double GetT0() { return t0_var; };
    double GetTot() { return tot_var; };
    double GetCharge() { return charge_var; };
    double GetAmplitude() { return amplitude_var; };
    double GetBaseline() { return baseline_var; };
    // functions to set variables
    void SetT0(double t0_val) { t0_var = t0_val; };
    void SetTot(double tot_val) { tot_var = tot_val; };
    void SetCharge(double charge_val) { charge_var = charge_val; };
    void SetAmplitude(double amplitude_val) { amplitude_var = amplitude_val; };
    void SetBaseline(double baseline_val) { baseline_var = baseline_val; };
    // functions to calculate variable with given histogram of the signal
    double CalcT0(TH1F *h_sig, double trigger);        // calc t0 based on trigger value, change value t0_var to calculated t0
    double CalcTot(TH1F *h_sig);                       // calculate time over threshold using CURRENT value of t0_var, change tot_var to calculated tot
    double CalcCharge(TH1F *h_sig, double time_limit); // calculate charge with upper limit of time time_limit, change charge_var to calculated charge
    double CalcAmplitude(TH1F *h_sig);                 // calculate amplitude, change value of amplitude_var to caluclated amplitude
    double CalcBaseline(TH1F *h_sig, double n_mean);   // calculate baseline, change value of baseline_var to caluculated baseline

    void ShiftBaseline(TH1F *h_sig); // shift baseline on histogram h_sig using CURRENT value of baseline_var

    ClassDef(MySignal, 1);
};
#endif
