model = build_model_from_rootfile('ROOTFILE',include_mc_uncertainties=True)


model.set_signal_processes('sig')

procs = model.processes


for proc in procs:
    
    #data driven
    if(proc=="NonPrompt"):
        model.add_lognormal_uncertainty("FakeRate",math.log(1.50),proc)
    elif(proc=="ChargeMisID"):
        model.add_lognormal_uncertainty("ChargeMisIDUnc",math.log(1.30),proc)
    #background MC
    elif(proc!="NonPrompt" and proc!='ChargeMisID' and proc!='sig'):
        #Common
        model.add_lognormal_uncertainty('pileup',math.log(1.06),proc)
        model.add_lognormal_uncertainty('lumi',math.log(1.05),proc)
        #lepton ID
        model.add_lognormal_uncertainty('LepIDEl_elmu',math.log(1.01),proc,'elmu')
        model.add_lognormal_uncertainty('LepIDMu_elmu',math.log(1.01),proc,'elmu')
        #lepton ISO
        model.add_lognormal_uncertainty('LepISOEl_elmu',math.log(1.01),proc,'elmu')
        model.add_lognormal_uncertainty('LepISOMu_elmu',math.log(1.01),proc,'elmu')
        #lepton Trig
        model.add_lognormal_uncertainty('LepTrig_elmu',math.log(1.03),proc,'elmu')

        #individual
        if(proc=='TTZ'):
            model.add_lognormal_uncertainty('MC',math.log(1.14),proc)
            model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
            model.add_lognormal_uncertainty('JER',math.log(1.02),proc)
        if(proc=='TTW'):
            model.add_lognormal_uncertainty('MC',math.log(1.20),proc)
            model.add_lognormal_uncertainty('JES',math.log(1.04),proc)
            model.add_lognormal_uncertainty('JER',math.log(1.02),proc)
        if(proc=='TTH'):
            model.add_lognormal_uncertainty('MC',math.log(1.13),proc)
            model.add_lognormal_uncertainty('JES',math.log(1.04),proc)
            model.add_lognormal_uncertainty('JER',math.log(1.02),proc)
        if(proc=='TTTT'):
            model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
            model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
            model.add_lognormal_uncertainty('JER',math.log(1.02),proc)
        if(proc=='WZ'):
            model.add_lognormal_uncertainty('MC',math.log(1.21),proc)
            model.add_lognormal_uncertainty('JES',math.log(1.08),proc)
            model.add_lognormal_uncertainty('JER',math.log(1.02),proc)
        if(proc=='ZZ'):
            model.add_lognormal_uncertainty('MC',math.log(1.12),proc)
            model.add_lognormal_uncertainty('JES',math.log(1.05),proc)
            model.add_lognormal_uncertainty('JER',math.log(1.02),proc)
        if(proc=='WpWp'):
            model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
            model.add_lognormal_uncertainty('JES',math.log(1.05),proc)
            model.add_lognormal_uncertainty('JER',math.log(1.02),proc)
        if(proc=='WWZ'):
            model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
            model.add_lognormal_uncertainty('JES',math.log(1.07),proc)
            model.add_lognormal_uncertainty('JER',math.log(1.02),proc)
        if(proc=='WZZ'):
            model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
            model.add_lognormal_uncertainty('JES',math.log(1.06),proc)
            model.add_lognormal_uncertainty('JER',math.log(1.02),proc)
        if(proc=='ZZZ'):
            model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
            model.add_lognormal_uncertainty('JES',math.log(1.06),proc)
            model.add_lognormal_uncertainty('JER',math.log(1.02),proc)

 #   signal
    else:
        model.add_lognormal_uncertainty('JER',math.log(1.01),proc)
        model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
        model.add_lognormal_uncertainty('PU',math.log(1.01),proc)
        model.add_lognormal_uncertainty('lumi',math.log(1.05),proc)                                        
        #lepton ID
        model.add_lognormal_uncertainty('LepIDEl_elmu',math.log(1.01),proc,'elmu')
        model.add_lognormal_uncertainty('LepIDMu_elmu',math.log(1.01),proc,'elmu')
#        lepton ISO
        model.add_lognormal_uncertainty('LepISOEl_elmu',math.log(1.01),proc,'elmu')
        model.add_lognormal_uncertainty('LepISOMu_elmu',math.log(1.01),proc,'elmu')
        #lepton Trig
        model.add_lognormal_uncertainty('LepTrig_elmu',math.log(1.03),proc,'elmu')
                                        
model_summary(model)

#Bayesian Limits
plot_exp, plot_obs = bayesian_limits(model,'all', n_toy = 10000, n_data = 1000)

plot_exp.write_txt('EXPTXTFILE')
plot_obs.write_txt('OBSTXTFILE')

signal_process_groups = {'sig': ['sig']}
import json
f = open('JSONNAME_discovery.json', 'w')
disc = discovery(model,use_data = False,input_expected='toys:XSEC',spid='sig',Z_error_max=0.1,ts_method=derll)
print disc
json.dump(disc, f)

#print "Asymptotic Limits:"
#print asymptotic_cls_limits(model, signal_processes=[['sig']], beta_signal_expected=0.0, bootstrap_model=True, input=None, n=1, options=None)

report.write_html('HTMLOUT')

