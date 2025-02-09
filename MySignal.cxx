#include "MySignal.h"
#include <cmath>

MySignal::MySignal(double t0_initial, double tot_initial, double charge_initial, double amplitude_initial, double baseline_initial) : t0_var(t0_initial), tot_var(tot_initial), amplitude_var(amplitude_initial), charge_var(charge_initial), baseline_var(baseline_initial)
{
}

MySignal::MySignal() : t0_var(0.0), tot_var(0.0), charge_var(0.0), amplitude_var(0.0), baseline_var(0.0)
{
}

MySignal::~MySignal()
{
}

double MySignal::CalcT0(TH1F *h_sig, double trigger)
{
    double t0 = 0;
    for (int i = 1; i < h_sig->GetNbinsX(); i++)
    {
        if (h_sig->GetBinContent(i) < trigger)
        {
            t0 = i;
            break;
        }
    }
    t0_var = t0;
    return t0;
}
double MySignal::CalcTot(TH1F *h_sig)
{
    double tot = 0;

    for (int i = t0_var; i < h_sig->GetNbinsX(); i++)
    {
        if (h_sig->GetBinContent(i) > h_sig->GetBinContent(t0_var))
        {
            tot = i;
            break;
        }
    }
    tot = tot - t0_var;
    tot_var = tot;
    return tot;
}

double MySignal::CalcCharge(TH1F *h_sig, double time_limit)
{
    double charge = 0;
    charge = h_sig->Integral(t0_var, time_limit);
    charge_var = charge;
    return charge;
}
double MySignal::CalcAmplitude(TH1F *h_sig)
{
    double amp = 10;
    for (int i = 1; i < h_sig->GetNbinsX(); i++)
    {
        double current_content = h_sig->GetBinContent(i);
        if (current_content < amp)
        {
            amp = current_content;
        }
    }
    amplitude_var = abs(amp);
    return amp;
}

double MySignal::CalcBaseline(TH1F *h_sig, double n_mean)
{
    double baseline = 0;

    for (int i = 1; i < n_mean; i++)
    {
        baseline += h_sig->GetBinContent(i);
    }

    baseline = baseline / n_mean;
    baseline_var = baseline;
    return baseline;
}

void MySignal::ShiftBaseline(TH1F *h_sig)
{
    for (int i = 1; i < h_sig->GetNbinsX(); i++)
    {
        h_sig->SetBinContent(i, h_sig->GetBinContent(i) - baseline_var);
    }
}
