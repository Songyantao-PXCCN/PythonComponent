# from 'SubscriptionService.ReadRecords'
O = ('None',(   (
                {'Arp.Plc.Eclr/M1.B': (False, 1592820481699459), 'Arp.Plc.Eclr/M1.A': (False, 1592820481699459)},
            ),
            (
                {'Arp.Plc.Eclr/B': (False, 1592820481700432), 'Arp.Plc.Eclr/A': (False, 1592820481700432)},
                {'Arp.Plc.Eclr/B': (False, 1592820481796731), 'Arp.Plc.Eclr/A': (False, 1592820481796731)},
                {'Arp.Plc.Eclr/B': (False, 1592820481896706), 'Arp.Plc.Eclr/A': (False, 1592820481896706)},
                {'Arp.Plc.Eclr/B': (False, 1592820481996693), 'Arp.Plc.Eclr/A': (False, 1592820481996693)},
                {'Arp.Plc.Eclr/B': (False, 1592820482096679), 'Arp.Plc.Eclr/A': (False, 1592820482096679)},
                {'Arp.Plc.Eclr/B': (False, 1592820482196706), 'Arp.Plc.Eclr/A': (False, 1592820482196706)},
                {'Arp.Plc.Eclr/B': (False, 1592820482296678), 'Arp.Plc.Eclr/A': (False, 1592820482296678)},
                {'Arp.Plc.Eclr/B': (False, 1592820482396673), 'Arp.Plc.Eclr/A': (False, 1592820482396673)},
                {'Arp.Plc.Eclr/B': (False, 1592820482496695), 'Arp.Plc.Eclr/A': (False, 1592820482496695)},
                {'Arp.Plc.Eclr/B': (False, 1592820482596704), 'Arp.Plc.Eclr/A': (False, 1592820482596704)}
            ),
            (
                {'Arp.Plc.Eclr/M2.B': (False, 1592820481796389), 'Arp.Plc.Eclr/M2.A': (False, 1592820481796389)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820481896383), 'Arp.Plc.Eclr/M2.A': (False, 1592820481896383)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820481996381), 'Arp.Plc.Eclr/M2.A': (False, 1592820481996381)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820482096367), 'Arp.Plc.Eclr/M2.A': (False, 1592820482096367)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820482196461), 'Arp.Plc.Eclr/M2.A': (False, 1592820482196461)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820482296377), 'Arp.Plc.Eclr/M2.A': (False, 1592820482296377)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820482396371), 'Arp.Plc.Eclr/M2.A': (False, 1592820482396371)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820482496372), 'Arp.Plc.Eclr/M2.A': (False, 1592820482496372)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820482596375), 'Arp.Plc.Eclr/M2.A': (False, 1592820482596375)},
                {'Arp.Plc.Eclr/M2.B': (False, 1592820482696385), 'Arp.Plc.Eclr/M2.A': (False, 1592820482696385)}
            )
        )
)



from datetime import datetime as dt

def ReadRecordsParse(records,Epoch = True):
    def EpochConvert(data):
        if data and type(data) == dict:
            for name,val in data.items():
                if val[1]>0:
                    v = dt.fromtimestamp(val[1]/ 1000000).strftime("%Y-%m-%dT%H:%M:%S.%f")
                    data[name] = (val[0],v)
                else:
                    data[name] = "inValid"
    print('*'*80)
    for i, tup in enumerate(records):
        if i is 0:
            print("- DataAccessError : "+'"'+tup+'"')
        else:
            print("- Records")
            for taskIndex,task in enumerate(tup):
                print('\t- Task '+str(taskIndex))
                for cycleIndex,cycle in enumerate(task):
                    if not Epoch:
                        EpochConvert(cycle)
                    print("\t\t- Cycle " + str(cycleIndex) + ' : ' + str(cycle))


ReadRecordsParse(O,False)

'''
- DataAccessError : "None"
- Records
	- Task 0
		- Cycle 0 : {'Arp.Plc.Eclr/M1.B': (False, 1592820481699459), 'Arp.Plc.Eclr/M1.A': (False, 1592820481699459)}
	- Task 1
		- Cycle 0 : {'Arp.Plc.Eclr/B': (False, 1592820481700432), 'Arp.Plc.Eclr/A': (False, 1592820481700432)}
		- Cycle 1 : {'Arp.Plc.Eclr/B': (False, 1592820481796731), 'Arp.Plc.Eclr/A': (False, 1592820481796731)}
		- Cycle 2 : {'Arp.Plc.Eclr/B': (False, 1592820481896706), 'Arp.Plc.Eclr/A': (False, 1592820481896706)}
		- Cycle 3 : {'Arp.Plc.Eclr/B': (False, 1592820481996693), 'Arp.Plc.Eclr/A': (False, 1592820481996693)}
		- Cycle 4 : {'Arp.Plc.Eclr/B': (False, 1592820482096679), 'Arp.Plc.Eclr/A': (False, 1592820482096679)}
		- Cycle 5 : {'Arp.Plc.Eclr/B': (False, 1592820482196706), 'Arp.Plc.Eclr/A': (False, 1592820482196706)}
		- Cycle 6 : {'Arp.Plc.Eclr/B': (False, 1592820482296678), 'Arp.Plc.Eclr/A': (False, 1592820482296678)}
		- Cycle 7 : {'Arp.Plc.Eclr/B': (False, 1592820482396673), 'Arp.Plc.Eclr/A': (False, 1592820482396673)}
		- Cycle 8 : {'Arp.Plc.Eclr/B': (False, 1592820482496695), 'Arp.Plc.Eclr/A': (False, 1592820482496695)}
		- Cycle 9 : {'Arp.Plc.Eclr/B': (False, 1592820482596704), 'Arp.Plc.Eclr/A': (False, 1592820482596704)}
	- Task 2
		- Cycle 0 : {'Arp.Plc.Eclr/M2.B': (False, 1592820481796389), 'Arp.Plc.Eclr/M2.A': (False, 1592820481796389)}
		- Cycle 1 : {'Arp.Plc.Eclr/M2.B': (False, 1592820481896383), 'Arp.Plc.Eclr/M2.A': (False, 1592820481896383)}
		- Cycle 2 : {'Arp.Plc.Eclr/M2.B': (False, 1592820481996381), 'Arp.Plc.Eclr/M2.A': (False, 1592820481996381)}
		- Cycle 3 : {'Arp.Plc.Eclr/M2.B': (False, 1592820482096367), 'Arp.Plc.Eclr/M2.A': (False, 1592820482096367)}
		- Cycle 4 : {'Arp.Plc.Eclr/M2.B': (False, 1592820482196461), 'Arp.Plc.Eclr/M2.A': (False, 1592820482196461)}
		- Cycle 5 : {'Arp.Plc.Eclr/M2.B': (False, 1592820482296377), 'Arp.Plc.Eclr/M2.A': (False, 1592820482296377)}
		- Cycle 6 : {'Arp.Plc.Eclr/M2.B': (False, 1592820482396371), 'Arp.Plc.Eclr/M2.A': (False, 1592820482396371)}
		- Cycle 7 : {'Arp.Plc.Eclr/M2.B': (False, 1592820482496372), 'Arp.Plc.Eclr/M2.A': (False, 1592820482496372)}
		- Cycle 8 : {'Arp.Plc.Eclr/M2.B': (False, 1592820482596375), 'Arp.Plc.Eclr/M2.A': (False, 1592820482596375)}
		- Cycle 9 : {'Arp.Plc.Eclr/M2.B': (False, 1592820482696385), 'Arp.Plc.Eclr/M2.A': (False, 1592820482696385)}
'''


'''
- DataAccessError : "None"
- Records
	- Task 0
		- Cycle 0 : {'Arp.Plc.Eclr/M1.B': (False, '2020-06-22T18:08:01.699459'), 'Arp.Plc.Eclr/M1.A': (False, '2020-06-22T18:08:01.699459')}
	- Task 1
		- Cycle 0 : {'Arp.Plc.Eclr/B': (False, '2020-06-22T18:08:01.700432'), 'Arp.Plc.Eclr/A': (False, '2020-06-22T18:08:01.700432')}
		- Cycle 1 : {'Arp.Plc.Eclr/B': (False, '2020-06-22T18:08:01.796731'), 'Arp.Plc.Eclr/A': (False, '2020-06-22T18:08:01.796731')}
		- Cycle 2 : {'Arp.Plc.Eclr/B': (False, '2020-06-22T18:08:01.896706'), 'Arp.Plc.Eclr/A': (False, '2020-06-22T18:08:01.896706')}
		- Cycle 3 : {'Arp.Plc.Eclr/B': (False, '2020-06-22T18:08:01.996693'), 'Arp.Plc.Eclr/A': (False, '2020-06-22T18:08:01.996693')}
		- Cycle 4 : {'Arp.Plc.Eclr/B': (False, '2020-06-22T18:08:02.096679'), 'Arp.Plc.Eclr/A': (False, '2020-06-22T18:08:02.096679')}
		- Cycle 5 : {'Arp.Plc.Eclr/B': (False, '2020-06-22T18:08:02.196706'), 'Arp.Plc.Eclr/A': (False, '2020-06-22T18:08:02.196706')}
		- Cycle 6 : {'Arp.Plc.Eclr/B': (False, '2020-06-22T18:08:02.296678'), 'Arp.Plc.Eclr/A': (False, '2020-06-22T18:08:02.296678')}
		- Cycle 7 : {'Arp.Plc.Eclr/B': (False, '2020-06-22T18:08:02.396673'), 'Arp.Plc.Eclr/A': (False, '2020-06-22T18:08:02.396673')}
		- Cycle 8 : {'Arp.Plc.Eclr/B': (False, '2020-06-22T18:08:02.496695'), 'Arp.Plc.Eclr/A': (False, '2020-06-22T18:08:02.496695')}
		- Cycle 9 : {'Arp.Plc.Eclr/B': (False, '2020-06-22T18:08:02.596704'), 'Arp.Plc.Eclr/A': (False, '2020-06-22T18:08:02.596704')}
	- Task 2
		- Cycle 0 : {'Arp.Plc.Eclr/M2.B': (False, '2020-06-22T18:08:01.796389'), 'Arp.Plc.Eclr/M2.A': (False, '2020-06-22T18:08:01.796389')}
		- Cycle 1 : {'Arp.Plc.Eclr/M2.B': (False, '2020-06-22T18:08:01.896383'), 'Arp.Plc.Eclr/M2.A': (False, '2020-06-22T18:08:01.896383')}
		- Cycle 2 : {'Arp.Plc.Eclr/M2.B': (False, '2020-06-22T18:08:01.996381'), 'Arp.Plc.Eclr/M2.A': (False, '2020-06-22T18:08:01.996381')}
		- Cycle 3 : {'Arp.Plc.Eclr/M2.B': (False, '2020-06-22T18:08:02.096367'), 'Arp.Plc.Eclr/M2.A': (False, '2020-06-22T18:08:02.096367')}
		- Cycle 4 : {'Arp.Plc.Eclr/M2.B': (False, '2020-06-22T18:08:02.196461'), 'Arp.Plc.Eclr/M2.A': (False, '2020-06-22T18:08:02.196461')}
		- Cycle 5 : {'Arp.Plc.Eclr/M2.B': (False, '2020-06-22T18:08:02.296377'), 'Arp.Plc.Eclr/M2.A': (False, '2020-06-22T18:08:02.296377')}
		- Cycle 6 : {'Arp.Plc.Eclr/M2.B': (False, '2020-06-22T18:08:02.396371'), 'Arp.Plc.Eclr/M2.A': (False, '2020-06-22T18:08:02.396371')}
		- Cycle 7 : {'Arp.Plc.Eclr/M2.B': (False, '2020-06-22T18:08:02.496372'), 'Arp.Plc.Eclr/M2.A': (False, '2020-06-22T18:08:02.496372')}
		- Cycle 8 : {'Arp.Plc.Eclr/M2.B': (False, '2020-06-22T18:08:02.596375'), 'Arp.Plc.Eclr/M2.A': (False, '2020-06-22T18:08:02.596375')}
		- Cycle 9 : {'Arp.Plc.Eclr/M2.B': (False, '2020-06-22T18:08:02.696385'), 'Arp.Plc.Eclr/M2.A': (False, '2020-06-22T18:08:02.696385')}

'''