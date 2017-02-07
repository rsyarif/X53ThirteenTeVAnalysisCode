

def getSSDLModel2016BD():
    model = build_model_from_rootfile('SSDLROOTFILE2016BD',include_mc_uncertainties=True)


    model.set_signal_processes('sig')
    
    procs = model.processes
    
    
    for proc in procs:
        
    #data driven
        if(proc=="NonPrompt"):
            model.add_lognormal_uncertainty("FakeRate",math.log(1.50),proc)
        elif(proc=="ChargeMisID"):
            model.add_lognormal_uncertainty("ChargeMisIDUnc",math.log(1.25),proc)
    #background MC
        elif(proc!="NonPrompt" and proc!='ChargeMisID' and proc!='sig'):
        #Common
            model.add_lognormal_uncertainty('pileup',math.log(1.06),proc)
            model.add_lognormal_uncertainty('lumi',math.log(1.12),proc)
        #lepton ID
            model.add_lognormal_uncertainty('elIdSys',math.log(1.02),proc,'elelBD')
        #lepton ISO
            model.add_lognormal_uncertainty('elIsoSys',math.log(1.02),proc,'elelBD')
        #lepton Trig
            model.add_lognormal_uncertainty('LepTrig2016BD_elel',math.log(1.03),proc,'elelBD')
            
        #individual
            if(proc=='TTZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.12),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='TTW'):
                model.add_lognormal_uncertainty('MC',math.log(1.20),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='TTH'):
                model.add_lognormal_uncertainty('MC',math.log(1.14),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='TTTT'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.02),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='WZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.12),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='ZZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.12),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.04),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='WpWp'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='WWZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='WZZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='ZZZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)

    #   signal
        else:
            model.add_lognormal_uncertainty('JetRes',math.log(1.01),proc)
            model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
            model.add_lognormal_uncertainty('PU',math.log(1.01),proc)
            model.add_lognormal_uncertainty('lumi',math.log(1.12),proc)                                        
        #lepton ID
            model.add_lognormal_uncertainty('elIdSys',math.log(1.02),proc,'elelBD')
        #lepton ISO
            model.add_lognormal_uncertainty('elIsoSys',math.log(1.02),proc,'elelBD')
        #lepton Trig
            model.add_lognormal_uncertainty('LepTrig2016BD_elel',math.log(1.03),proc,'elelBD')


    return model


def getSSDLModel_2016EH():
    model = build_model_from_rootfile('SSDLROOTFILE2016EH',include_mc_uncertainties=True)


    model.set_signal_processes('sig')
    
    procs = model.processes
    
    
    for proc in procs:
        
    #data driven
        if(proc=="NonPrompt"):
            model.add_lognormal_uncertainty("FakeRate",math.log(1.50),proc)
        elif(proc=="ChargeMisID"):
            model.add_lognormal_uncertainty("ChargeMisIDUnc",math.log(1.25),proc)
    #background MC
        elif(proc!="NonPrompt" and proc!='ChargeMisID' and proc!='sig'):
        #Common
            model.add_lognormal_uncertainty('pileup',math.log(1.06),proc)
            model.add_lognormal_uncertainty('lumi',math.log(1.12),proc)
        #lepton ID
            model.add_lognormal_uncertainty('elIdSys',math.log(1.02),proc,'elelEH')
        #lepton ISO
            model.add_lognormal_uncertainty('elIsoSys',math.log(1.02),proc,'elelEH')
        #lepton Trig
            model.add_lognormal_uncertainty('LepTrig2016EH_elel',math.log(1.03),proc,'elelEH')
            
        #individual
            if(proc=='TTZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.12),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='TTW'):
                model.add_lognormal_uncertainty('MC',math.log(1.20),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='TTH'):
                model.add_lognormal_uncertainty('MC',math.log(1.14),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='TTTT'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.02),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='WZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.12),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='ZZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.12),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.04),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='WpWp'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='WWZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='WZZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)
            if(proc=='ZZZ'):
                model.add_lognormal_uncertainty('MC',math.log(1.50),proc)
                model.add_lognormal_uncertainty('JES',math.log(1.09),proc)
                model.add_lognormal_uncertainty('JetRes',math.log(1.02),proc)

    #   signal
        else:
            model.add_lognormal_uncertainty('JetRes',math.log(1.01),proc)
            model.add_lognormal_uncertainty('JES',math.log(1.03),proc)
            model.add_lognormal_uncertainty('PU',math.log(1.01),proc)
            model.add_lognormal_uncertainty('lumi',math.log(1.12),proc)                                        
        #lepton ID
            model.add_lognormal_uncertainty('elIdSys',math.log(1.02),proc,'elelEH')
        #lepton ISO
            model.add_lognormal_uncertainty('elIsoSys',math.log(1.02),proc,'elelEH')
        #lepton Trig
            model.add_lognormal_uncertainty('LepTrig2016EH_elel',math.log(1.03),proc,'elelEH')


    return model

ssdlModel1 = getSSDLModel2016BD()
ssdlModel12= getSSDLModel2016EH()


ssdlModel1.combine(ssdlModel2)
                                        
model_summary(ssdlModel1)

#Bayesian Limits
plot_exp, plot_obs = bayesian_limits(ssdlModel,'all', n_toy = 5000, n_data = 500)

plot_exp.write_txt('EXPTXTFILE')
plot_obs.write_txt('OBSTXTFILE')

signal_process_groups = {'sig': ['sig']}
import json
f = open('JSONNAME_discovery.json', 'w')
disc = discovery(ssdlModel,use_data = False,input_expected='toys:XSEC',spid='sig',Z_error_max=0.1,ts_method=derll)
print disc
json.dump(disc, f)

#print "Asymptotic Limits:"
#print asymptotic_cls_limits(ssdlModel, signal_processes=[['sig']], beta_signal_expected=0.0, bootstrap_ssdlModel=True, input=None, n=1, options=None)

report.write_html('HTMLOUT')

