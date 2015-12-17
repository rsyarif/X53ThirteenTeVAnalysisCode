model = higgs_datacard.build_model('CARDFILE',include_mc_uncertainties=True)


model.set_signal_processes('sig')

procs = model.processes


for proc in procs:
    
    #data driven
    if(proc=="NonPrompt"):
        model.add_lognormal_uncertainty("FakeRate",math.log(1.50),proc)
    elif(proc=="ChargeMisID"):
        model.add_lognormal_uncertainty("ChargeMisIDUnc",math.log(1.30),proc)
    #background MC
#    elif(proc!="NonPrompt" and proc!='ChargeMisID' and proc!='sig'):
        #Common
#        model.add_lognormal_uncertainty('pileup',math.log(1.06),proc)
#        model.add_lognormal_uncertainty('lumi',math.log(1.12),proc)
        #individual
#        if(proc=='TTZ'):
#            model.add_lognormal_uncertainty('TTZMC',math.log(1.12),proc)
#            model.add_lognormal_uncertainty('TTZJES',math.log(1.03),proc)
#            model.add_lognormal_uncertainty('TTZJER',math.log(1.02),proc)
#        if(proc=='TTW'):
#            model.add_lognormal_uncertainty('TTWMC',math.log(1.20),proc)
#            model.add_lognormal_uncertainty('TTWJES',math.log(1.04),proc)
#            model.add_lognormal_uncertainty('TTWJER',math.log(1.02),proc)
#        if(proc=='TTH'):
#            model.add_lognormal_uncertainty('TTHMC',math.log(1.14),proc)
#            model.add_lognormal_uncertainty('TTHJES',math.log(1.08),proc)
#            model.add_lognormal_uncertainty('TTHJER',math.log(1.02),proc)
#        if(proc=='TTTT'):
#            model.add_lognormal_uncertainty('TTTTMC',math.log(1.50),proc)
#            model.add_lognormal_uncertainty('TTTTJES',math.log(1.06),proc)
#            model.add_lognormal_uncertainty('TTTTJER',math.log(1.02),proc)
#        if(proc=='WZ'):
#            model.add_lognormal_uncertainty('WZMC',math.log(1.12),proc)
#            model.add_lognormal_uncertainty('WZJES',math.log(1.05),proc)
#            model.add_lognormal_uncertainty('WZJER',math.log(1.02),proc)
#        if(proc=='ZZ'):
#            model.add_lognormal_uncertainty('ZZMC',math.log(1.12),proc)
#            model.add_lognormal_uncertainty('ZZJES',math.log(1.04),proc)
#            model.add_lognormal_uncertainty('ZZJER',math.log(1.02),proc)
#        if(proc=='WpWp'):
#            model.add_lognormal_uncertainty('WpWpMC',math.log(1.50),proc)
#            model.add_lognormal_uncertainty('WpWpJES',math.log(1.04),proc)
#            model.add_lognormal_uncertainty('WpWpJER',math.log(1.02),proc)
#        if(proc=='WWZ'):
#            model.add_lognormal_uncertainty('WWZMC',math.log(1.50),proc)
 #           model.add_lognormal_uncertainty('WWZJES',math.log(1.04),proc)
 #           model.add_lognormal_uncertainty('WWZJER',math.log(1.02),proc)
 #       if(proc=='WZZ'):
 #           model.add_lognormal_uncertainty('WZZMC',math.log(1.50),proc)
 #           model.add_lognormal_uncertainty('WZZJES',math.log(1.06),proc)
 #           model.add_lognormal_uncertainty('WZZJER',math.log(1.02),proc)
 #       if(proc=='ZZZ'):
 #           model.add_lognormal_uncertainty('ZZZMC',math.log(1.50),proc)
  #          model.add_lognormal_uncertainty('ZZZJES',math.log(1.06),proc)
  #          model.add_lognormal_uncertainty('ZZZJER',math.log(1.02),proc)

    #signal
 #   else:
   #     model.add_lognormal_uncertainty('sigJER',math.log(1.01),proc)
   #     model.add_lognormal_uncertainty('sigJES',math.log(1.03),proc)
   #     model.add_lognormal_uncertainty('sigPU',math.log(1.01),proc)
#        model.add_lognormal_uncertainty('lumi',math.log(1.12),proc)                                        
                                        
model_summary(model)

#Bayesian Limits
plot_exp, plot_obs = bayesian_limits(model,'all', n_toy = 2000, n_data = 500)

plot_exp.write_txt('EXPTXTFILE')
plot_obs.write_txt('OBSTXTFILE')

#signal_process_groups = {'sig': ['sig']}
#import json
#f = open('JSONNAME_discovery.json', 'w')
#disc = discovery(model,use_data = False,input_expected='toys:XSEC',spid='sig',Z_error_max=0.1,ts_method=derll)
#print disc
#json.dump(disc, f)

#print "Asymptotic Limits:"
#print asymptotic_cls_limits(model, signal_processes=[['sig']], beta_signal_expected=0.0, bootstrap_model=True, input=None, n=1, options=None)

report.write_html('HTMLOUT')

