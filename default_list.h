// Liste des intitules de Defauts	

char szItemDefault[1000][166] = {	
"Aucune panne detectee",	// P0000
"Commande de regulateur de volume de carburant - circuit ouvert",	// P0001
"Commande de regulateur de volume de carburant - plage de mesure/performance du circuit",	// P0002
"Commande de regulateur de volume de carburant - circuit trop bas",	// P0003
"Commande de regulateur de volume de carburant - circuit trop haut",	// P0004
"Electrovanne de coupure carburant - circuit ouvert",	// P0005
"Electrovanne de coupure carburant - circuit trop bas",	// P0006
"Electrovanne de coupure carburant - circuit trop haut",	// P0007
"Calage moteur, ligne 1 - performance du moteur",	// P0008
"Calage moteur, ligne 2 - performance du moteur",	// P0009
"Capteur d'arbre a cames d'admission, ligne 1 - panne du circuit",	// P0010
"Position d'arbre a cames, ligne 1 - calage excessivement avance/performance du systeme",	// P0011
"Position d'arbre a cames, ligne 1 - calage excessivement retarde",	// P0012
"Capteur d'arbre a cames d'echappement, ligne 1 - panne du circuit",	// P0013
"Capteur d'arbre a cames d'echappement, ligne 1 - calage excessivement avance/performance du systeme",	// P0014
"Capteur d'arbre a cames d'echappement, ligne 1 - calage excessivement retarde",	// P0015
"Position du vilebrequin/position d'arbre a cames, ligne 1 capteur A - correlation",	// P0016
"Position du vilebrequin/position d'arbre a cames, ligne 1 capteur B - correlation",	// P0017
"Position du vilebrequin/position d'arbre a cames, ligne 2 capteur A - correlation",	// P0018
"Position du vilebrequin/position d'arbre a cames, ligne 2 capteur B - correlation",	// P0019
"Capteur d'arbre a cames d'admission, ligne 2 - panne du circuit",	// P0020
"Position d'arbre a cames d'admission, ligne 2 - calage excessivement avance",	// P0021
"Position d'arbre a cames d'admission, ligne 2 - calage excessivement retarde",	// P0022
"Capteur d'arbre a cames d'echappement, ligne 2 - panne du circuit",	// P0023
"Position d'arbre a cames d'echappement, ligne 2 - calage excessivement avance",	// P0024
"Position d'arbre a cames d'echappement, ligne 2 - calage excessivement retarde",	// P0025
"Systeme electrovanne de commande de soupape d'admission, ligne 1 - plage de mesure/performance",	// P0026
"Systeme electrovanne de commande de soupape d'echappement, ligne 1 - plage de mesure/performance",	// P0027
"Systeme electrovanne de commande de soupape d'admission, ligne 2 - plage de mesure/performance",	// P0028
"Systeme electrovanne de commande de soupape d'echappement, ligne 2 - plage de mesure/performance",	// P0029
"Sonde Lambda 1, ligne 1, commande de chauffage - panne du circuit",	// P0030
"Sonde Lambda 1, ligne 1, commande de chauffage - circuit trop bas",	// P0031
"Sonde Lambda 1, ligne 1, commande de chauffage - circuit trop haut",	// P0032
"Electrovanne de decharge du turbocompresseur - panne du circuit",	// P0033
"Electrovanne de decharge du turbocompresseur - circuit trop bas",	// P0034
"Electrovanne de decharge du turbocompresseur - circuit trop haut",	// P0035
"Sonde Lambda 2, ligne 1 , commande de chauffage - panne du circuit",	// P0036
"Sonde Lambda 2, ligne 1 , commande de chauffage - circuit trop bas",	// P0037
"Sonde Lambda 2, ligne 1 , commande de chauffage - circuit trop haut",	// P0038
"Soupape de derivation du compresseur/turbocompresseur, circuit de commande - plage de mesure/performance",	// P0039
"Signaux sondes Lambda inversees, ligne 1 capteur 1/ligne 2 capteur 1",	// P0040
"Signaux sondes Lambda inversees, ligne 1 capteur 2/ligne 2 capteur 2",	// P0041
"Sonde Lambda 3, ligne 1 , commande de chauffage - panne du circuit",	// P0042
"Sonde Lambda 3, ligne 1 , commande de chauffage - circuit trop bas",	// P0043
"Sonde Lambda 3, ligne 1 , commande de chauffage - circuit trop haut",	// P0044
"Electrovanne de commande de la pression de suralimentation - circuit ouvert",	// P0045
"Electrovanne de commande de la pression de suralimentation du compresseur/turbocompresseur - plage de mesure/performance du circuit",	// P0046
"Electrovanne de commande de la pression de suralimentation du compresseur/turbocompresseur - circuit trop bas",	// P0047
"Electrovanne de commande de la pression de suralimentation du compresseur/turbocompresseur - circuit trop haut",	// P0048
"Turbine de compresseur/turbocompresseur - regime excessif",	// P0049
"Sonde Lambda 1, ligne 2, commande de chauffage - panne du circuit",	// P0050
"Sonde Lambda 1, ligne 2, commande de chauffage - circuit trop bas",	// P0051
"Sonde Lambda 1, ligne 2, commande de chauffage - circuit trop haut",	// P0052
"Sonde Lambda, ligne 1 , capteur 1 - resistance du chauffage",	// P0053
"Sonde Lambda, ligne 1 , capteur 2 - resistance du chauffage",	// P0054
"Sonde Lambda, ligne 1 , capteur 3 - resistance du chauffage",	// P0055
"Sonde Lambda 2, ligne 2, commande de chauffage - panne du circuit",	// P0056
"Sonde Lambda 2, ligne 2, commande de chauffage - circuit de chauffage trop faible",	// P0057
"Sonde Lambda 2, ligne 2, commande de chauffage - circuit trop haut",	// P0058
"Sonde Lambda, ligne 2, capteur 1 - resistance du chauffage",	// P0059
"Sonde Lambda, ligne 2, capteur 2 - resistance du chauffage",	// P0060
"Sonde Lambda, ligne 2, capteur 3 -resistance du chauffage",	// P0061
"Sonde Lambda 3, ligne 2, commande de chauffage - panne du circuit",	// P0062
"Sonde Lambda 3, ligne 2, commande de chauffage - circuit trop bas",	// P0063
"Sonde Lambda 3, ligne 2, commande de chauffage - circuit trop haut",	// P0064
"Injecteur assiste par air comprime - probleme de performance/de limites",	// P0065
"Injecteur assiste par air comprime - panne du circuit/circuit trop bas",	// P0066
"Injecteur assiste par air comprime - circuit trop haut",	// P0067
"Correlation capteur de pression absolue du collecteur d'admission/debitmetre d'air/position du papillon",	// P0068
"Correlation capteur de pression absolue du collecteur d'admission/capteur de pression atmospherique",	// P0069
"Sonde de temperature exterieure - panne du circuit",	// P0070
"Sonde de temperature exterieure - probleme de performance/de limites",	// P0071
"Sonde de temperature exterieure - valeur d'entree trop basse",	// P0072
"Sonde de temperature exterieure - valeur d'entree trop haute",	// P0073
"Sonde de temperature exterieure - circuit intermittent",	// P0074
"Electrovanne de commande de soupape d'admission, ligne 1 - panne du circuit",	// P0075
"Electrovanne de commande de soupape d'admission, ligne 1 - circuit trop bas",	// P0076
"Electrovanne de commande de soupape d'admission, ligne 1 - circuit trop haut",	// P0077
"Electrovanne de commande de soupape d'echappement ligne 1 - panne du circuit",	// P0078
"Electrovanne de commande de soupape d'echappement ligne 1 - circuit trop bas",	// P0079
"Electrovanne de commande de soupape d'echappement ligne 1 - circuit trop haut",	// P0080
"Electrovanne de commande de soupape d'admission, ligne 2 - panne du circuit",	// P0081
"Electrovanne de commande de soupape d'admission, ligne 2 - circuit trop bas",	// P0082
"Electrovanne de commande de soupape d'admission, ligne 2 - circuit trop haut",	// P0083
"Electrovanne de commande de soupape d'echappement ligne 2 - panne du circuit",	// P0084
"Electrovanne de commande de soupape d'echappement ligne 2 - circuit trop bas",	// P0085
"Electrovanne de commande de soupape d'echappement ligne 2 - circuit trop haut",	// P0086
"Rampe de distribution/pression du systeme trop faible",	// P0087
"Rampe de distribution/pression du systeme trop haute",	// P0088
"Regulateur de pression du carburant - probleme de performance",	// P0089
"Electrovanne de dosage de carburant - circuit ouvert",	// P0090
"Electrovanne de dosage de carburant - court-circuit sur masse",	// P0091
"Electrovanne de dosage de carburant - court-circuit sur l'alimentation",	// P0092
"Fuite dans le systeme d'alimentation en carburant - fuite importante detectee",	// P0093
"Fuite dans le systeme d'alimentation en carburant - petit fuite detectee",	// P0094
"Sonde de temperature d'air 2 - panne du circuit",	// P0095
"Sonde de temperature d'air 2 - plage de mesure/performance du circuit",	// P0096
"Sonde de temperature d'air 2 - signal d'entree du circuit trop bas",	// P0097
"Sonde de temperature d'air 2 - signal d'entree du circuit trop haut",	// P0098
"Sonde de temperature d'air 2 - circuit intermittent/irregulier",	// P0099
"Debitmetre d'air - panne du circuit",	// P0100
"Debitmetre d'air - probleme de performance/de limites",	// P0101
"Debitmetre d'air - valeur d'entree trop basse",	// P0102
"Debitmetre d'air - valeur d'entree trop haute",	// P0103
"Debitmetre d'air - circuit intermittent",	// P0104
"Capteur de pression absolue du collecteur d'admission/capteur de pression atmospherique - panne du circuit",	// P0105
"Capteur de pression absolue du collecteur d'admission/capteur de pression atmospherique - probleme de performance/de limites",	// P0106
"Capteur de pression absolue du collecteur d'admission/capteur de pression atmospherique - valeur d'entree trop basse",	// P0107
"Capteur de pression absolue du collecteur d'admission/capteur de pression atmospherique - valeur d'entree trop haute",	// P0108
"Capteur de pression absolue du collecteur d'admission/capteur de pression atmospherique - circuit intermittent",	// P0109
"Sonde de temperature d'air - panne du circuit",	// P0110
"Sonde de temperature d'air - probleme de performance/de limites",	// P0111
"Sonde de temperature d'air - valeur d'entree trop basse",	// P0112
"Sonde de temperature d'air - valeur d'entree trop haute",	// P0113
"Sonde de temperature d'air - circuit intermittent",	// P0114
"Sonde de temperature du liquide de refroidissement - panne du circuit",	// P0115
"Sonde de temperature du liquide de refroidissement - probleme de performance/de limites",	// P0116
"Sonde de temperature du liquide de refroidissement - valeur d'entree trop basse",	// P0117
"Sonde de temperature du liquide de refroidissement - valeur d'entree trop haute",	// P0118
"Sonde de temperature du liquide de refroidissement - circuit intermittent",	// P0119
"Capteur de position de papillon A/capteur de position de la pedale d'accelerateur A - panne du circuit",	// P0120
"Capteur de position de papillon A/capteur de position de la pedale d'accelerateur A - probleme de performance/de limites",	// P0121
"Capteur de position de papillon A/capteur de position de la pedale d'accelerateur A - valeur d'entree trop basse",	// P0122
"Capteur de position de papillon A/capteur de position de la pedale d'accelerateur A - valeur d'entree trop haute",	// P0123
"Capteur de position de papillon A/capteur de position de la pedale d'accelerateur A - circuit intermittent",	// P0124
"Temperature du liquide de refroidissement insuffisante pour commande en boucle fermee",	// P0125
"Temperature du liquide de refroidissement insuffisante pour un fonctionnement stable",	// P0126
"Temperature d'air d'admission trop haute",	// P0127
"Thermostat du liquide de refroidissement - temperature du liquide de refroidissement inferieure a la temperature de regulation du thermostat",	// P0128
"Pression atmospherique trop basse",	// P0129
"Sonde Lambda 1, ligne 1 - panne du circuit",	// P0130
"Sonde Lambda 1, ligne 1 - signal bas",	// P0131
"Sonde Lambda 1, ligne 1 - signal haut",	// P0132
"Sonde Lambda 1, ligne 1 - reponse lente",	// P0133
"Sonde Lambda 1, ligne 1 - pas d'activite detectee",	// P0134
"Sonde Lambda 1, ligne 1 - commande de chauffage - panne de circuit",	// P0135
"Sonde Lambda 2, ligne 1 - panne du circuit",	// P0136
"Sonde Lambda 2, ligne 1 - signal bas",	// P0137
"Sonde Lambda 2, ligne 1 - signal haut",	// P0138
"Sonde Lambda 2, ligne 1 - reponse lente",	// P0139
"Sonde Lambda 2, ligne 1 - pas d'activite detectee",	// P0140
"Sonde Lambda 2, ligne 1 - commande de chauffage - panne de circuit",	// P0141
"Sonde Lambda 3, ligne 1 - panne du circuit",	// P0142
"Sonde Lambda 3, ligne 1 - signal bas",	// P0143
"Sonde Lambda 3, ligne 1 - signal haut",	// P0144
"Sonde Lambda 3, ligne 1 - reponse lente",	// P0145
"Sonde Lambda 3, ligne 1 - pas d'activite detectee",	// P0146
"Sonde Lambda 3, ligne 1 - commande de chauffage - panne de circuit",	// P0147
"Erreur de debit de carburant",	// P0148
"Erreur de calage d'injection",	// P0149
"Sonde Lambda 1, ligne 2 - panne du circuit",	// P0150
"Sonde Lambda 1, ligne 2 - signal bas",	// P0151
"Sonde Lambda 1, ligne 2 - signal haut",	// P0152
"Sonde Lambda 1, ligne 2 - reponse lente",	// P0153
"Sonde Lambda 1, ligne 2 - pas d'activite detectee",	// P0154
"Sonde Lambda 1, ligne 2 - commande de chauffage - panne de circuit",	// P0155
"Sonde Lambda 2, ligne 2 - panne du circuit",	// P0156
"Sonde Lambda 2, ligne 2 - signal bas",	// P0157
"Sonde Lambda 2, ligne 2 - signal haut",	// P0158
"Sonde Lambda 2, ligne 2 - reponse lente",	// P0159
"Sonde Lambda 2, ligne 2 - pas d'activite detectee",	// P0160
"Sonde Lambda 2, ligne 2 - commande de chauffage - panne de circuit",	// P0161
"Sonde Lambda 3, ligne 2 - panne du circuit",	// P0162
"Sonde Lambda 3, ligne 2 - signal bas",	// P0163
"Sonde Lambda 3, ligne 2 - signal haut",	// P0164
"Sonde Lambda 3, ligne 2 - reponse lente",	// P0165
"Sonde Lambda 3, ligne 2 - pas d'activite detectee",	// P0166
"Sonde Lambda 3, ligne 2 - commande de chauffage - panne de circuit",	// P0167
"Temperature du carburant trop haute",	// P0168
"Erreur de composition du carburant",	// P0169
"Ajustement du carburant, ligne 1 - panne",	// P0170
"Ajustement du carburant, ligne 1 - panne",	// P0171
"Melange trop riche, ligne 1",	// P0172
"Ajustement du carburant, ligne 2 - panne",	// P0173
"Melange trop pauvre, ligne 2",	// P0174
"Melange trop riche, ligne 2",	// P0175
"Capteur de composition du carburant - panne du circuit",	// P0176
"Capteur de composition du carburant - probleme de performance/de limites",	// P0177
"Capteur de composition du carburant - valeur d'entree trop basse",	// P0178
"Capteur de composition du carburant - valeur d'entree trop haute",	// P0179
"Sonde de temperature du carburant A - panne du circuit",	// P0180
"Sonde de temperature du carburant A - probleme de performance/de limites",	// P0181
"Sonde de temperature du carburant A - valeur d'entree trop basse",	// P0182
"Sonde de temperature du carburant A - valeur d'entree trop haute",	// P0183
"Sonde de temperature du carburant A - circuit intermittent",	// P0184
"Sonde de temperature du carburant B - panne du circuit",	// P0185
"Sonde de temperature du carburant B - probleme de performance/de limites",	// P0186
"Sonde de temperature du carburant B - valeur d'entree trop basse",	// P0187
"Sonde de temperature du carburant B - valeur d'entree trop haute",	// P0188
"Sonde de temperature du carburant B - circuit intermittent",	// P0189
"Capteur de pression de la rampe de distribution - panne du circuit",	// P0190
"Capteur de pression de la rampe de distribution - probleme de performance/de limites",	// P0191
"Capteur de pression de la rampe de distribution - valeur d'entree trop basse",	// P0192
"Capteur de pression de la rampe de distribution - valeur d'entree trop haute",	// P0193
"Capteur de pression de la rampe de distribution - circuit intermittent",	// P0194
"Sonde de temperature d'huile moteur - panne du circuit",	// P0195
"Sonde de temperature d'huile moteur - probleme de performance/de limites",	// P0196
"Sonde de temperature d'huile moteur - valeur d'entree trop basse",	// P0197
"Sonde de temperature d'huile moteur - valeur d'entree trop haute",	// P0198
"Sonde de temperature d'huile moteur - circuit intermittent",	// P0199
"Injecteur - panne du circuit",	// P0200
"Injecteur 1 - panne du circuit",	// P0201
"Injecteur 2 - panne du circuit",	// P0202
"Injecteur 3 - panne du circuit",	// P0203
"Injecteur 4 - panne du circuit",	// P0204
"Injecteur 5 - panne du circuit",	// P0205
"Injecteur 6 - panne du circuit",	// P0206
"Injecteur 7 - panne du circuit",	// P0207
"Injecteur 8 - panne du circuit",	// P0208
"Injecteur 9 - panne du circuit",	// P0209
"Injecteur 10 - panne du circuit",	// P0210
"Injecteur 11 - panne du circuit",	// P0211
"Injecteur 12 - panne du circuit",	// P0212
"Injecteur de depart a froid 1 - panne du circuit",	// P0213
"Injecteur de depart a froid 2 - panne du circuit",	// P0214
"Electrovanne de coupure de carburant - panne du circuit",	// P0215
"Commande de calage d'injection - panne du circuit",	// P0216
"Surchauffe du moteur",	// P0217
"Surchauffe de la transmission",	// P0218
"Regime excessif",	// P0219
"Capteur de position de papillon B/capteur de position de la pedale d'accelerateur B - panne du circuit",	// P0220
"Capteur de position de papillon B/capteur de position de la pedale d'accelerateur B - probleme de performance/de limites",	// P0221
"Capteur de position de papillon B/capteur de position de la pedale d'accelerateur B- valeur d'entree trop basse",	// P0222
"Capteur de position de papillon B/capteur de position de la pedale d'accelerateur B - valeur d'entree trop haute",	// P0223
"Capteur de position de papillon B/capteur de position de la pedale d'accelerateur B - circuit intermittent",	// P0224
"Capteur de position de papillon C/capteur de position de la pedale d'accelerateur C - panne du circuit",	// P0225
"Capteur de position de papillon C/capteur de position de la pedale d'accelerateur C - probleme de performance/de limites",	// P0226
"Capteur de position de papillon C/capteur de position de la pedale d'accelerateur C - valeur d'entree trop basse",	// P0227
"Capteur de position de papillon C/capteur de position de la pedale d'accelerateur C- valeur d'entree trop haute",	// P0228
"Capteur de position de papillon C/capteur de position de la pedale d'accelerateur C- circuit intermittent",	// P0229
"Circuit primaire de pompe a carburant - panne du circuit",	// P0230
"Circuit secondaire de pompe a carburant - circuit trop bas",	// P0231
"Circuit secondaire de pompe a carburant - circuit trop haut",	// P0232
"Circuit secondaire de pompe a carburant - circuit intermittent",	// P0233
"Condition de suralimentation du moteur - limite depassee",	// P0234
"Capteur de pression absolue du collecteur d'admission A, circuit du turbocompresseur - panne du circuit",	// P0235
"Capteur de pression absolue du collecteur d'admission A, circuit du turbocompresseur - probleme de performance/de limites",	// P0236
"Capteur de pression absolue du collecteur d'admission A, circuit du turbocompresseur - valeur d'entree trop basse",	// P0237
"Capteur de pression absolue du collecteur d'admission A, circuit du turbocompresseur - valeur d'entree trop haute",	// P0238
"Capteur de pression absolue du collecteur d'admission B, circuit du turbocompresseur - panne du circuit",	// P0239
"Capteur de pression absolue du collecteur d'admission B, circuit du turbocompresseur - probleme de performance/de limites",	// P0240
"Capteur de pression absolue du collecteur d'admission B, circuit du turbocompresseur - valeur d'entree trop basse",	// P0241
"Capteur de pression absolue du collecteur d'admission B, circuit du turbocompresseur - valeur d'entree trop haute",	// P0242
"Electrovanne de decharge du turbocompresseur A - panne du circuit",	// P0243
"Electrovanne de decharge du turbocompresseur A - probleme de performance/de limites",	// P0244
"Electrovanne de decharge du turbocompresseur A - circuit trop bas",	// P0245
"Electrovanne de decharge du turbocompresseur A - circuit trop haut",	// P0246
"Electrovanne de decharge du turbocompresseur B - panne du circuit",	// P0247
"Electrovanne de decharge du turbocompresseur B - probleme de performance/de limites",	// P0248
"Electrovanne de decharge du turbocompresseur B - circuit trop bas",	// P0249
"Electrovanne de decharge du turbocompresseur B - circuit trop haut",	// P0250
"Pompe d'injection A, rotor/cames - panne du circuit",	// P0251
"Pompe d'injection A, rotor/cames - probleme de performance/de limites",	// P0252
"Pompe d'injection A, rotor/cames - circuit trop bas",	// P0253
"Pompe d'injection A, rotor/cames - circuit trop haut",	// P0254
"Pompe d'injection A, rotor/cames - circuit intermittent",	// P0255
"Pompe d'injection B, rotor/cames - panne du circuit",	// P0256
"Pompe d'injection B, rotor/cames - probleme de performance/de limites",	// P0257
"Pompe d'injection B, rotor/cames - circuit trop bas",	// P0258
"Pompe d'injection B, rotor/cames - circuit trop haut",	// P0259
"Pompe d'injection B, rotor/cames - circuit intermittent",	// P0260
"Injecteur 1 - circuit trop bas",	// P0261
"Injecteur 1 - circuit trop haut",	// P0262
"Cylindre 1 - Quantite de fuel injecte - defaut d'equilibrage",	// P0263
"Injecteur 2 - circuit trop bas",	// P0264
"Injecteur 2 - circuit trop haut",	// P0265
"Cylindre 2 - Quantite de fuel injecte - defaut d'equilibrage",	// P0266
"Injecteur 3 - circuit trop bas",	// P0267
"Injecteur 3 - circuit trop haut",	// P0268
"Cylindre 3 - Quantite de fuel injecte - defaut d'equilibrage",	// P0269
"Injecteur 4 - circuit trop bas",	// P0270
"Injecteur 4 - circuit trop haut",	// P0271
"Cylindre 4 - Quantite de fuel injecte - defaut d'equilibrage",	// P0272
"Injecteur 5 - circuit trop bas",	// P0273
"Injecteur 5 - circuit trop haut",	// P0274
"Cylindre 5 - Quantite de fuel injecte - defaut d'equilibrage",	// P0275
"Injecteur 6 - circuit trop bas",	// P0276
"Injecteur 6 - circuit trop haut",	// P0277
"Cylindre 6 - Quantite de fuel injecte - defaut d'equilibrage",	// P0278
"Injecteur 7 - circuit trop bas",	// P0279
"Injecteur 7 - circuit trop haut",	// P0280
"Cylindre 7 - Quantite de fuel injecte - defaut d'equilibrage",	// P0281
"Injecteur 8 - circuit trop bas",	// P0282
"Injecteur 8 - circuit trop haut",	// P0283
"Cylindre 8 - Quantite de fuel injecte - defaut d'equilibrage",	// P0284
"Injecteur 9 - circuit trop bas",	// P0285
"Injecteur 9 - circuit trop haut",	// P0286
"Cylindre 9 - Quantite de fuel injecte - defaut d'equilibrage",	// P0287
"Injecteur 10 - circuit trop bas",	// P0288
"Injecteur 10 - circuit trop haut",	// P0289
"Cylindre 10 - Quantite de fuel injecte - defaut d'equilibrage",	// P0290
"Injecteur 11 - circuit trop bas",	// P0291
"Injecteur 11 - circuit trop haut",	// P0292
"Cylindre 11 - Quantite de fuel injecte - defaut d'equilibrage",	// P0293
"Injecteur 12 - circuit trop bas",	// P0294
"Injecteur 12 - circuit trop haut",	// P0295
"Cylindre 12 - Quantite de fuel injecte - defaut d'equilibrage",	// P0296
"Vitesse excessive vehicule",	// P0297
"Temperature d'huile moteur trop haute",	// P0298
"Compresseur/turbocompresseur - pression de suralimentation faible",	// P0299
"Cylindre(s) multiple(s) - rates d'allumage aleatoire detectes",	// P0300
"Cylindre 1 - rates d'allumage detectes",	// P0301
"Cylindre 2 - rates d'allumage detectes",	// P0302
"Cylindre 3 - rates d'allumage detectes",	// P0303
"Cylindre 4 - rates d'allumage detectes",	// P0304
"Cylindre 5 - rates d'allumage detectes",	// P0305
"Cylindre6 - rates d'allumage detectes",	// P0306
"Cylindre7 - rates d'allumage detectes",	// P0307
"Cylindre8 - rates d'allumage detectes",	// P0308
"Cylindre9 - rates d'allumage detectes",	// P0309
"Cylindre10 - rates d'allumage detectes",	// P0310
"Cylindre11 - rates d'allumage detectes",	// P0311
"Cylindre12 - rates d'allumage detectes",	// P0312
"Rates d'allumage detectes avec niveau de carburant trop bas",	// P0313
"Rate d'allumage dans un seul cylindre - cylindre non specifie",	// P0314
"Crankshaft Position System Variation Not Learned",	// P0315
"Rates d'allumage detectes au demarrage - dans les 1000 premiers tours moteur",	// P0316
"Composant detecteur de route accidentee absent",	// P0317
"Signal du detecteur de route accidentee A - panne du circuit",	// P0318
"Signal du detecteur de route accidentee B - panne du circuit",	// P0319
"Capteur de vilebrequin/de regime - panne du circuit",	// P0320
"Capteur de vilebrequin/de regime - probleme de performance/de limites",	// P0321
"Capteur de vilebrequin/de regime - aucun signal",	// P0322
"Capteur de vilebrequin/de regime - circuit intermittent",	// P0323
"Erreur de systeme anti-cliquetis",	// P0324
"Detecteur de cliquetis 1, ligne 1 - panne du circuit",	// P0325
"Detecteur de cliquetis 1, ligne 1 - probleme de performance/de limites",	// P0326
"Detecteur de cliquetis 1, ligne 1 - valeur d'entree trop basse",	// P0327
"Detecteur de cliquetis 1, ligne 1 - valeur d'entree trop haute",	// P0328
"Detecteur de cliquetis 1, ligne 1 - circuit intermittent",	// P0329
"Detecteur de cliquetis 2, ligne 2 - panne du circuit",	// P0330
"Detecteur de cliquetis 2, ligne 2 - probleme de performance/de limites",	// P0331
"Detecteur de cliquetis 2, ligne 2 - valeur d'entree trop basse",	// P0332
"Detecteur de cliquetis 2, ligne 2 - valeur d'entree trop haute",	// P0333
"Detecteur de cliquetis 2, ligne 2 - circuit intermittent",	// P0334
"Capteur de vilebrequin - panne du circuit",	// P0335
"Capteur de vilebrequin - probleme de performance/de limites",	// P0336
"Capteur de vilebrequin - valeur d'entree trop basse",	// P0337
"Capteur de vilebrequin - valeur d'entree trop haute",	// P0338
"Capteur de vilebrequin - circuit intermittent",	// P0339
"Capteur d'arbre a cames A ligne 1 - panne du circuit",	// P0340
"Capteur d'arbre a cames A ligne 1 - probleme de performance/de limites",	// P0341
"Capteur d'arbre a cames A ligne 1 - valeur d'entree trop basse",	// P0342
"Capteur d'arbre a cames A ligne 1 - valeur d'entree trop haute",	// P0343
"Capteur d'arbre a cames A ligne 1 - circuit intermittent",	// P0344
"Capteur d'arbre a cames A ligne 2 - panne du circuit",	// P0345
"Capteur d'arbre a cames A ligne 2 - probleme de performance/de limites",	// P0346
"Capteur d'arbre a cames A ligne 2 - valeur d'entree trop basse",	// P0347
"Capteur d'arbre a cames A ligne 2 - valeur d'entree trop haute",	// P0348
"Capteur d'arbre a cames A ligne 2 - circuit intermittent",	// P0349
"Bobine d'allumage, primaire/secondaire - panne du circuit",	// P0350
"Bobine d'allumage A, primaire/secondaire - panne du circuit",	// P0351
"Bobine d'allumage B, primaire/secondaire - panne du circuit",	// P0352
"Bobine d'allumage C, primaire/secondaire - panne du circuit",	// P0353
"Bobine d'allumage D, primaire/secondaire - panne du circuit",	// P0354
"Bobine d'allumage E, primaire/secondaire - panne du circuit",	// P0355
"Bobine d'allumage F, primaire/secondaire - panne du circuit",	// P0356
"Bobine d'allumage G, primaire/secondaire - panne du circuit",	// P0357
"Bobine d'allumage H, primaire/secondaire - panne du circuit",	// P0358
"Bobine d'allumage I, primaire/secondaire - panne du circuit",	// P0359
"Bobine d'allumage J, primaire/secondaire - panne du circuit",	// P0360
"Bobine d'allumage K, primaire/secondaire - panne du circuit",	// P0361
"Bobine d'allumage L, primaire/secondaire - panne du circuit",	// P0362
"Rates d'allumage detectes - alimentation en carburant desactivee",	// P0363
"Bobine d'allumage L, primaire/secondaire - panne du circuit",	// P0364
"Capteur d'arbre a cames B, ligne 1 - panne du circuit",	// P0365
"Capteur d'arbre a cames B, ligne 1 - plage de mesure/performance du circuit",	// P0366
"Capteur d'arbre a cames B, ligne 1 - signal d'entree du circuit trop bas",	// P0367
"Capteur d'arbre a cames B, ligne 1 - signal d'entree du circuit trop haut",	// P0368
"Capteur d'arbre a cames B, ligne 1 - circuit intermittent",	// P0369
"Reference de calage, signal haute resolution A - panne",	// P0370
"Reference de calage, signal haute resolution A - trop de signaux",	// P0371
"Reference de calage, signal haute resolution A - trop peu de signaux",	// P0372
"Reference de calage, signal haute resolution A - signaux irreguliers intermittents",	// P0373
"Reference de calage, signal haute resolution A - pas de signaux",	// P0374
"Reference de calage, signal haute resolution B - panne",	// P0375
"Reference de calage, signal haute resolution B - trop de signaux",	// P0376
"Reference de calage, signal haute resolution B - trop peu de signaux",	// P0377
"Reference de calage, signal haute resolution B - signaux irreguliers intermittents",	// P0378
"Reference de calage, signal haute resolution B - pas de signaux",	// P0379
"Bougies de prechauffage, circuit A - panne",	// P0380
"Lampe temoin bougies de prechauffage - panne du circuit",	// P0381
"Bougies de prechauffage, circuit B - panne",	// P0382
"Commande du module des bougies de prechauffage - bas",	// P0383
"Commande du module des bougies de prechauffage - haut",	// P0384
"Capteur de vilebrequin B - panne du circuit",	// P0385
"Capteur de vilebrequin B - probleme de performance/de limites",	// P0386
"Capteur de vilebrequin B - valeur d'entree trop basse",	// P0387
"Capteur de vilebrequin B - valeur d'entree trop haute",	// P0388
"Capteur de vilebrequin B - circuit intermittent",	// P0389
"Capteur d'arbre a cames B, ligne 2 - panne du circuit",	// P0390
"Capteur d'arbre a cames B, ligne 2 - plage de mesure/performance du circuit",	// P0391
"Capteur d'arbre a cames B, ligne 2 - signal d'entree du circuit trop bas",	// P0392
"Capteur d'arbre a cames B, ligne 2 - signal d'entree du circuit trop haut",	// P0393
"Capteur d'arbre a cames B, ligne 2 - circuit intermittent",	// P0394
"Capteur d'arbre a cames B, ligne 2 - signal d'entree du circuit trop haut",	// P0395
"Capteur d'arbre a cames B, ligne 2 - circuit intermittent",	// P0396
"",	// P0397
"",	// P0398
"",	// P0399
"Systeme EGR - probleme de debit",	// P0400
"Systeme EGR - debit insuffisant detecte",	// P0401
"Systeme EGR - debit excessif detecte",	// P0402
"Recyclage des gaz d'echappement - panne du circuit",	// P0403
"Systeme EGR - probleme de performance/de limites",	// P0404
"Capteur de position de la valve EGR A - valeur d'entree trop basse",	// P0405
"Capteur de position de la valve EGR A - valeur d'entree trop haute",	// P0406
"Capteur de position de la valve EGR B - valeur d'entree trop basse",	// P0407
"Capteur de position de la valve EGR B - valeur d'entree trop haute",	// P0408
"Capteur EGR A - panne du circuit",	// P0409
"Systeme d'injection d'air secondaire - panne",	// P0410
"Systeme d'injection d'air secondaire - debit incorrect detecte",	// P0411
"Electrovanne d'injection d'air secondaire A - panne du circuit",	// P0412
"Electrovanne d'injection d'air secondaire A - circuit ouvert",	// P0413
"Electrovanne d'injection d'air secondaire A - courtcircuit",	// P0414
"Electrovanne d'injection d'air secondaire B - panne du circuit",	// P0415
"Electrovanne d'injection d'air secondaire B - circuit ouvert",	// P0416
"Electrovanne d'injection d'air secondaire B - courtcircuit",	// P0417
"Relais de la pompe d'injection d'air secondaire A - panne du circuit",	// P0418
"Relais de la pompe d'injection d'air secondaire B - panne du circuit",	// P0419
"Circuit de catalyseur, ligne 1 - rendement inferieur au seuil",	// P0420
"Pre-catalyseur, ligne 1 - rendement inferieur au seuil",	// P0421
"Catalyseur principal, ligne 1 - rendement inferieur au seuil",	// P0422
"Catalyseur chauffe, ligne 1 - rendement inferieur au seuil",	// P0423
"Catalyseur chauffe, ligne 1 - temperature inferieur au seuil",	// P0424
"Sonde de temperature du catalyseur, ligne 1",	// P0425
"Sonde de temperature du catalyseur, ligne 1 - plage de mesure/performance",	// P0426
"Sonde de temperature du catalyseur, ligne 1 - valeur d'entree trop basse",	// P0427
"Sonde de temperature du catalyseur, ligne 1 - valeur d'entree trop haute",	// P0428
"Chauffage catalyseur, ligne 1 - panne du circuit de commande",	// P0429
"Circuit de catalyseur, ligne 2 - rendement inferieur au seuil",	// P0430
"Pre-catalyseur, ligne 2 - rendement inferieur au seuil",	// P0431
"Catalyseur principal, ligne 2 - rendement inferieur au seuil",	// P0432
"Catalyseur chauffe, ligne 2 - rendement inferieur au seuil",	// P0433
"Catalyseur chauffe, ligne 2 - temperature inferieur au seuil",	// P0434
"Sonde de temperature du catalyseur, ligne 2",	// P0435
"Sonde de temperature du catalyseur, ligne 2 - plage de mesure/performance",	// P0436
"Sonde de temperature du catalyseur, ligne 2 - valeur d'entree trop basse",	// P0437
"Sonde de temperature du catalyseur, ligne 2 - valeur d'entree trop haute",	// P0438
"Chauffage catalyseur, ligne 2 - panne du circuit",	// P0439
"Systeme de purge canister - panne",	// P0440
"Systeme de purge canister - debit incorrect detecte",	// P0441
"Systeme de purge canister - petite fuite detectee",	// P0442
"Electrovanne de purge canister - panne du circuit",	// P0443
"Electrovanne de purge canister - circuit ouvert",	// P0444
"Electrovanne de purge canister - courtcircuit",	// P0445
"Systeme de purge canister, commande de ventilation - panne du circuit",	// P0446
"Systeme de purge canister, commande de ventilation - circuit ouvert",	// P0447
"Systeme de purge canister, commande de ventilation - court-circuit",	// P0448
"Systeme de purge canister, soupape de ventilation - panne du circuit",	// P0449
"Capteur de pression de purge canister - panne du circuit",	// P0450
"Capteur de pression de purge canister - probleme de performance/de limites",	// P0451
"Capteur de pression de purge canister - valeur d'entree trop basse",	// P0452
"Capteur de pression de purge canister - valeur d'entree trop haute",	// P0453
"Capteur de pression de purge canister - circuit intermittent",	// P0454
"Systeme de purge canister - fuite importante detectee",	// P0455
"Systeme de purge canister - tres petite fuite detectee",	// P0456
"Systeme de purge canister - fuite detectee",	// P0457
"Systeme de purge canister, electrovanne de purge canister - circuit trop bas",	// P0458
"Systeme de purge canister, electrovanne de purge canister - circuit trop haut",	// P0459
"Sonde de niveau du reservoir de carburant - panne du circuit",	// P0460
"Sonde de niveau du reservoir de carburant - probleme de performance/de limites",	// P0461
"Sonde de niveau du reservoir de carburant - valeur d'entree trop basse",	// P0462
"Sonde de niveau du reservoir de carburant - valeur d'entree trop haute",	// P0463
"Sonde de niveau du reservoir de carburant - circuit intermittent",	// P0464
"Capteur de flux de purge canister - panne du circuit",	// P0465
"Capteur de flux de purge canister - probleme de performance/de limites",	// P0466
"Capteur de flux de purge canister - valeur d'entree trop basse",	// P0467
"Capteur de flux de purge canister - valeur d'entree trop haute",	// P0468
"Capteur de flux de purge canister - circuit intermittent",	// P0469
"Capteur de pression des gaz d'echappement - panne du circuit",	// P0470
"Capteur de pression des gaz d'echappement - probleme de performance/de limites",	// P0471
"Capteur de pression des gaz d'echappement - valeur d'entree trop basse",	// P0472
"Capteur de pression des gaz d'echappement - valeur d'entree trop haute",	// P0473
"Capteur de pression des gaz d'echappement - circuit intermittent",	// P0474
"Electrovanne de commande de pression des gaz d'echappement-panne du circuit",	// P0475
"Electrovanne de commande de pression des gaz d'echappement-probleme de performance/de limites",	// P0476
"Electrovanne de commande de pression des gaz d'echappement - valeur d'entree trop basse",	// P0477
"Electrovanne de commande de pression des gaz d'echappement - valeur d'entree trop haute",	// P0478
"Electrovanne de commande de pression des gaz d'echappement- circuit intermittent",	// P0479
"Motoventilateur de refroidissement 1 - panne du circuit",	// P0480
"Motoventilateur de refroidissement 2 - panne du circuit",	// P0481
"Motoventilateur de refroidissement 3 - panne du circuit",	// P0482
"Motoventilateur de refroidissement, contrôle de rationalite - panne",	// P0483
"Motoventilateur de refroidissement - surcharge du circuit",	// P0484
"Motoventilateur de refroidissement, alimentation/masse - panne du circuit",	// P0485
"Capteur de position de la valve EGR B - panne du circuit",	// P0486
"Systeme EGR, commande de position du papillon - panne du circuit",	// P0487
"Systeme EGR, commande de position du papillon - plage de mesure/performance",	// P0488
"Systeme EGR - circuit trop bas",	// P0489
"Systeme EGR - circuit trop haut",	// P0490
"Systeme d'injection d'air secondaire, ligne 1 - panne",	// P0491
"Systeme d'injection d'air secondaire, ligne 2 - panne",	// P0492
"Vitesse motoventilateur de refroidissement moteur - excessive",	// P0493
"Vitesse motoventilateur de refroidissement moteur - basse",	// P0494
"Vitesse motoventilateur de refroidissement moteur - haute",	// P0495
"Systeme de purge canister - flux de purge eleve",	// P0496
"Systeme de purge canister - flux de purge faible",	// P0497
"Systeme de purge canister, commande de ventilation - circuit trop bas",	// P0498
"Systeme de purge canister, commande de ventilation - circuit trop haut",	// P0499
"Capteur de vitesse du vehicule - panne du circuit",	// P0500
"Capteur de vitesse du vehicule - probleme de performance/de limites",	// P0501
"Capteur de vitesse du vehicule - valeur d'entree trop basse",	// P0502
"Capteur de vitesse du vehicule - valeur d'entree intermittente/irreguliere/trop haute",	// P0503
"Contacteur de freinage - correlation A/B",	// P0504
"Commande du ralenti - panne",	// P0505
"Commande du ralenti - regime plus lent que prevu",	// P0506
"Commande du ralenti - regime plus rapide que prevu",	// P0507
"Commande d'air au ralenti - circuit trop bas",	// P0508
"Commande d'air au ralenti - circuit trop haut",	// P0509
"Contacteur de position fermee de papillon - panne du circuit",	// P0510
"Commande d'air au ralenti - panne du circuit",	// P0511
"Circuit de commande du demarreur - panne",	// P0512
"Cle de l'antidemarrage incorrecte",	// P0513
"Sonde de temperature batterie - plage de mesure/performance du circuit",	// P0514
"Sonde de temperature batterie - panne du circuit",	// P0515
"Sonde de temperature batterie - circuit trop bas",	// P0516
"Sonde de temperature batterie - circuit trop haut",	// P0517
"Commande d'air au ralenti - circuit intermittent",	// P0518
"Commande d'air au ralenti - performance circuit",	// P0519
"Capteur de pression/pressostat d'huile moteur - panne du circuit",	// P0520
"Capteur de pression/pressostat d'huile moteur - probleme de performance/de limites",	// P0521
"Capteur de pression/pressostat d'huile moteur - basse tension",	// P0522
"Capteur de pression/pressostat d'huile moteur - haute tension",	// P0523
"Pression d'huile moteur trop basse",	// P0524
"Regulateur de vitesse, commande d'actuateur - plage de mesure/performance du circuit",	// P0525
"Capteur de vitesse du motoventilateur de refroidissement moteur- panne du circuit",	// P0526
"Capteur de vitesse du motoventilateur de refroidissement moteur - plage de mesure/performance du circuit",	// P0527
"Capteur de vitesse du motoventilateur de refroidissement moteur - aucun signal",	// P0528
"Capteur de vitesse du motoventilateur de refroidissement moteur - circuit intermittent",	// P0529
"Capteur de pression du refrigerant de la climatisation - panne du circuit",	// P0530
"Capteur de pression du refrigerant de la climatisation - probleme de performance/de limites",	// P0531
"Capteur de pression du refrigerant de la climatisation - valeur d'entree trop basse",	// P0532
"Capteur de pression du refrigerant de la climatisation - valeur d'entree trop haute",	// P0533
"Perte de charge du refrigerant de la climatisation",	// P0534
"Sonde de temperature de l'evaporateur climatisation - panne du circuit",	// P0535
"Sonde de temperature de l'evaporateur climatisation - plage de mesure/performance du circuit",	// P0536
"Sonde de temperature de l'evaporateur climatisation - circuit trop bas",	// P0537
"Sonde de temperature de l'evaporateur climatisation - circuit trop haut",	// P0538
"Sonde de temperature de l'evaporateur climatisation - circuit intermittent",	// P0539
"Chauffage d'air d'admission A - panne du circuit",	// P0540
"Chauffage d'air d'admission A - circuit trop bas",	// P0541
"Chauffage d'air d'admission A - circuit trop haut",	// P0542
"Chauffage d'air d'admission A - circuit ouvert",	// P0543
"Sonde de temperature EGR, ligne 1 - panne du circuit",	// P0544
"Sonde de temperature EGR, ligne 1 - valeur d'entree trop basse",	// P0545
"Sonde de temperature EGR, ligne 1 - valeur d'entree trop haute",	// P0546
"Sonde de temperature des gaz d'echappement, ligne 2 capteur 1 - panne du circuit",	// P0547
"Sonde de temperature des gaz d'echappement, ligne 2 capteur 1 - circuit trop bas",	// P0548
"Sonde de temperature des gaz d'echappement, ligne 2 capteur 1 - circuit trop haut",	// P0549
"Capteur/pressostat de direction assistee - panne du circuit",	// P0550
"Capteur/pressostat de direction assistee - probleme de performance/de limites",	// P0551
"Capteur/pressostat de direction assistee - valeur d'entree trop basse",	// P0552
"Capteur/pressostat de direction assistee - valeur d'entree trop haute",	// P0553
"Capteur/pressostat de direction assistee - circuit intermittent",	// P0554
"Capteur de pression du servofrein - panne du circuit",	// P0555
"Capteur de pression du servofrein - plage de mesure/performance du circuit",	// P0556
"Capteur de pression du servofrein - signal d'entree du circuit trop bas",	// P0557
"Capteur de pression du servofrein - signal d'entree du circuit trop haut",	// P0558
"Capteur de pression du servofrein - circuit intermittent",	// P0559
"Tension du systeme - panne",	// P0560
"Tension du systeme - instable",	// P0561
"Tension du systeme - basse",	// P0562
"Tension du systeme - haute",	// P0563
"Regulateur de vitesse, signal d'entree A du contacteur multifonction - panne du circuit",	// P0564
"Commutateur principal du regulateur de vitesse, signal de marche (ON) - panne",	// P0565
"Commutateur principal du regulateur de vitesse, signal d'arrÃªt (OFF) - panne",	// P0566
"Selecteur de reprise du regulateur de vitesse - panne",	// P0567
"Commutateur principal du regulateur de vitesse, signal SET - panne",	// P0568
"Selecteur du regulateur de vitesse, signal COAST - panne",	// P0569
"Regulateur de vitesse, signal du capteur de position de la pedale - panne",	// P0570
"Contacteur de regulateur de vitesse/de freinage A - panne du circuit",	// P0571
"Contacteur de regulateur de vitesse/de freinage A - circuit trop bas",	// P0572
"Contacteur de regulateur de vitesse/de freinage A - circuit trop haut",	// P0573
"Regulateur de vitesse - vitesse trop haute",	// P0574
"Regulateur de vitesse - panne du circuit d'entree",	// P0575
"Regulateur de vitesse - circuit d'entree trop faible",	// P0576
"Regulateur de vitesse - circuit d'entree trop fort",	// P0577
"Regulateur de vitesse, signal d'entree A du contacteur multifonction - circuit bloque",	// P0578
"Regulateur de vitesse, signal d'entree A du contacteur multifonction - plage de mesure/performance du circuit",	// P0579
"Regulateur de vitesse, signal d'entree A du contacteur multifonction - circuit trop bas",	// P0580
"Regulateur de vitesse, signal d'entree A du contacteur multifonction - circuit trop haut",	// P0581
"Regulateur de vitesse, commande par depression - circuit ouvert",	// P0582
"Regulateur de vitesse, commande par depression - circuit trop bas",	// P0583
"Regulateur de vitesse, commande par depression - circuit trop haut",	// P0584
"Regulateur de vitesse, signal d'entree A/B du contacteur multifonction - correlation",	// P0585
"Regulateur de vitesse, commande de ventilation - circuit ouvert",	// P0586
"Regulateur de vitesse, commande de ventilation - circuit trop bas",	// P0587
"Regulateur de vitesse, commande de ventilation - circuit trop haut",	// P0588
"Regulateur de vitesse, signal d'entree B du contacteur multifonction - panne du circuit",	// P0589
"Regulateur de vitesse, signal d'entree B du contacteur multifonction - circuit bloque",	// P0590
"Regulateur de vitesse, signal d'entree B du contacteur multifonction -plage de mesure/performance du circuit",	// P0591
"Regulateur de vitesse, signal d'entree B du contacteur multifonction - circuit trop bas",	// P0592
"Regulateur de vitesse, signal d'entree B du contacteur multifonction - circuit trop haut",	// P0593
"Regulateur de vitesse, commande d'actuateur - circuit ouvert",	// P0594
"Regulateur de vitesse, commande d'actuateur - circuit trop bas",	// P0595
"Regulateur de vitesse, commande d'actuateur - circuit trop haut",	// P0596
"Dispositif de commande du chauffage a thermostat - circuit ouvert",	// P0597
"Dispositif de commande du chauffage a thermostat - circuit trop bas",	// P0598
"Dispositif de commande du chauffage a thermostat - circuit trop haut",	// P0599
"Bus de donnees CAN - panne",	// P0600
"Calculateur de gestion moteur - erreur du total de contrôle de memoire",	// P0601
"Calculateur de gestion moteur - erreur de programmation",	// P0602
"Calculateur de gestion moteur - erreur KAM",	// P0603
"Calculateur de gestion moteur - erreur RAM",	// P0604
"Calculateur de gestion moteur - erreur ROM",	// P0605
"Calculateur de gestion moteur/calculateur combine moteur-transmission",	// P0606
"Calculateur/boitier electronique - probleme de performance - panne de processeur",	// P0607
"Calculateur de gestion moteur, signal de sortie du capteur de vitesse du vehicule A - panne",	// P0608
"Calculateur de gestion moteur, signal de sortie du capteur de vitesse du vehicule B - panne",	// P0609
"Calculateur/boitier electronique - erreur options vehicule",	// P0610
"Boitier electronique d'injecteur de carburant - probleme de performance",	// P0611
"Boitier electronique d'injecteur carburant - circuit du relais de commande",	// P0612
"Calculateur de transmission - erreur de processeur",	// P0613
"Calculateur de gestion moteur/calculateur de transmission - desaccord",	// P0614
"Relais du demarreur - panne du circuit de gestion moteur",	// P0615
"Relais du demarreur - circuit trop bas de gestion moteur",	// P0616
"Relais du demarreur - circuit trop haut calculateur de gestion moteur",	// P0617
"Boitier electronique carburant alternatif - erreur KAM",	// P0618
"Boitier electronique carburant alternatif - erreur RAM/ROM",	// P0619
"Alternateur, commande - panne du circuit",	// P0620
"Alternateur - lampe temoin de charge L - panne du circuit",	// P0621
"Alternateur - lampe temoin de charge F - panne du circuit",	// P0622
"Lampe temoin de charge - panne du circuit",	// P0623
"Lampe temoin trappe du reservoir de carburant - panne du circuit",	// P0624
"Borne champ du generateur - circuit trop bas",	// P0625
"Borne champ du generateur - circuit trop haut",	// P0626
"Commande de pompe a carburant - circuit ouvert",	// P0627
"Commande de pompe a carburant - circuit trop bas",	// P0628
"Commande de pompe a carburant - circuit trop haut",	// P0629
"VIN non programme ou desaccord d'identification - calculateur de gestion moteur/calculateur transmission/gestion moteur",	// P0630
"VIN non programme ou desaccord d'identification - calculateur de transmission",	// P0631
"Compteur kilometrique non programme - calculateur de gestion moteur/calculateur transmission/gestion moteur",	// P0632
"Cle de l'antidemarrage non programmee - calculateur de gestion moteur/calculateur transmission/gestion moteur",	// P0633
"Calculateur transmission/gestion moteur/calculateur de gestion moteur/calculateur de transmission - temperature interne trop haute",	// P0634
"Commande direction assistee - panne du circuit",	// P0635
"Commande direction assistee - circuit trop bas",	// P0636
"Commande direction assistee - circuit trop haut",	// P0637
"Commande d'actuateur de papillon, ligne 1 - probleme de performance/de limites",	// P0638
"Commande d'actuateur de papillon, ligne 2 - plage mesure/performance",	// P0639
"Commande de chauffage d'air d'admission - panne du circuit",	// P0640
"Tension de reference du capteur A - circuit ouvert",	// P0641
"Calculateur de gestion moteur, anti-c1iquetis - defectueux",	// P0642
"Tension de reference du capteur A - circuit trop haut",	// P0643
"Affichage conducteur, communication de series de donnees - panne du circuit",	// P0644
"Relais d'embrayage du compresseur de climatisation",	// P0645
"Relais embrayage du compresseur de climatisation - circuit trop bas",	// P0646
"Relais embrayage du compresseur de climatisation - circuit trop haut",	// P0647
"Lampe temoin antidemarrage - panne du circuit",	// P0648
"Lampe temoin regulateur de vitesse - circuit moteur",	// P0649
"Lampe temoin d'affichage des defauts - panne du circuit",	// P0650
"Tension de reference du capteur B - circuit ouvert",	// P0651
"Tension de reference du capteur B - circuit trop bas",	// P0652
"Tension de reference du capteur B - circuit trop haut",	// P0653
"Regime moteur, sortie - panne du circuit",	// P0654
"Signal de sortie du temoin de surchauffe du moteur - panne du circuit",	// P0655
"Signal de sortie de niveau de carburant - panne du circuit",	// P0656
"Tension d'alimentation d'actuateur - circuit ouvert",	// P0657
"Tension d'alimentation d'actuateur - circuit trop bas",	// P0658
"Tension d'alimentation d'actuateur - circuit trop haut",	// P0659
"Electrovanne d'admission d'air dans le collecteur, ligne 1 - circuit ouvert",	// P0660
"Electrovanne d'admission d'air dans le collecteur, ligne 1 - circuit trop bas",	// P0661
"Electrovanne d'admission d'air dans le collecteur, ligne 1 - circuit trop haut",	// P0662
"Electrovanne d'admission d'air dans le collecteur, ligne 2 - circuit ouvert",	// P0663
"Electrovanne d'admission d'air dans le collecteur, ligne 2 - circuit trop bas",	// P0664
"Electrovanne d'admission d'air dans le collecteur, ligne 2 - circuit trop haut",	// P0665
"Sonde de temperature interne calculateur combine moteur-transmission/ calculateur de gestion moteur/calculateur de transmission - panne du circuit",	// P0666
"Sonde de temperature interne calculateur combine moteur-transmission/ calculateur de gestion moteur/calculateur de transmission - plage de mesure/performance",	// P0667
"Sonde de temperature interne calculateur combine moteur-transmission/ calculateur de gestion moteur/calculateur de transmission - circuit trop bas",	// P0668
"Sonde de temperature interne calculateur combine moteur-transmission/calculateur de gestion moteur/calculateur de transmission - circuit trop haut",	// P0669
"Boitier electronique des bougies de prechauffage - panne du circuit",	// P0670
"Bougies de prechauffage, cylindre 1 - panne du circuit",	// P0671
"Bougies de prechauffage, cylindre 2 - panne du circuit",	// P0672
"Bougies de prechauffage, cylindre 3 - panne du circuit",	// P0673
"Bougies de prechauffage, cylindre 4 - panne du circuit",	// P0674
"Bougies de prechauffage, cylindre 5 - panne du circuit",	// P0675
"Bougies de prechauffage, cylindre 6 - panne du circuit",	// P0676
"Bougies de prechauffage, cylindre 7 - panne du circuit",	// P0677
"Bougies de prechauffage, cylindre 8 - panne du circuit",	// P0678
"Bougies de prechauffage, cylindre 9 - panne du circuit",	// P0679
"Bougies de prechauffage, cylindre 10 - panne du circuit",	// P0680
"Bougies de prechauffage, cylindre 11 - panne du circuit",	// P0681
"Bougies de prechauffage, cylindre 12 - panne du circuit",	// P0682
"Communication boitier electronique des bougies de prechauffage/ calculateur de gestion moteur/calculateur combine moteur-transmission - panne",	// P0683
"Communication boitier electronique des bougies de prechauffage/calculateur de gestion moteur/calculateur combine moteur-transmission - plage de mesure/performance",	// P0684
"Relais d'alimentation electrique calculateur de gestion moteur/calculateur combine transmission-gestion moteur - circuit ouvert",	// P0685
"Relais d'alimentation electrique calculateur de gestion moteur/calculateur combine transmission-gestion moteur - circuit trop bas",	// P0686
"Relais de gestion du moteur - court-circuit sur la masse",	// P0687
"Relais de gestion du moteur - court-circuit sur l'alimentation",	// P0688
"Relais d'alimentation electrique calculateur de gestion moteur/calculateur combine transmission-gestion moteur - circuit de sondage trop faible",	// P0689
"Relais d'alimentation electrique calculateur de gestion moteur/calculateur combine transmission-gestion moteur - circuit de sondage trop fort",	// P0690
"Motoventilateur de refroidissement 1 - courtcircuit sur la masse",	// P0691
"Motoventilateur de refroidissement 1 - courtcircuit sur l'alimentation",	// P0692
"Motoventilateur de refroidissement 2 - courtcircuit sur la masse",	// P0693
"Motoventilateur de refroidissement 2 - courtcircuit sur l'alimentation",	// P0694
"Motoventilateur de refroidissement 3 - courtcircuit sur la masse",	// P0695
"Motoventilateur de refroidissement 3 - courtcircuit sur l'alimentation",	// P0696
"Tension de reference du capteur C - circuit ouvert",	// P0697
"Tension de reference du capteur C - circuit trop bas",	// P0698
"Tension de reference du capteur C - circuit trop haut",	// P0699
"Commande de la transmission - panne",	// P0700
"Commande de la transmission - probleme de performance/de limites",	// P0701
"Commande de la transmission - electrique",	// P0702
"Convertisseur de couple/contacteur de freinage B - panne du circuit",	// P0703
"Contacteur de position de la pedale d'embrayage - panne du circuit",	// P0704
"Contacteur/capteur de position du levier de vitesse, signal d'entree PIRMIDL - panne du circuit",	// P0705
"Contacteur/capteur de position du levier de vitesse - probleme de performance/de limites",	// P0706
"Contacteur/capteur de position du levier de vitesse - valeur d'entree trop basse",	// P0707
"Contacteur/capteur de position du levier de vitesse - valeur d'entree trop haute",	// P0708
"Contacteur/capteur de position du levier de vitesse - circuit intermittent",	// P0709
"Sonde de temperature d'huile de transmission - panne du circuit",	// P0710
"Sonde de temperature d'huile de transmission - probleme de performance/de limites",	// P0711
"Sonde de temperature d'huile de transmission - valeur d'entree trop basse",	// P0712
"Sonde de temperature d'huile de transmission - valeur d'entree trop haute",	// P0713
"Sonde de temperature d'huile de transmission - circuit intermittent",	// P0714
"Capteur de vitesse d'arbre de turbine - panne du circuit",	// P0715
"Capteur de vitesse d'arbre de turbine - probleme de performance/de limites",	// P0716
"Capteur de vitesse d'arbre de turbine - aucun signal",	// P0717
"Capteur de vitesse d'arbre de turbine - circuit intermittent",	// P0718
"Convertisseur de couple/contacteur de freinage B - circuit trop bas",	// P0719
"Capteur de vitesse du vehicule - panne du circuit",	// P0720
"Capteur de vitesse du vehicule - probleme de performance/de limites",	// P0721
"Capteur de vitesse du vehicule - aucun signal",	// P0722
"Capteur de vitesse du vehicule - circuit intermittent",	// P0723
"Convertisseur de couple/contacteur de freinage B - circuit trop haut",	// P0724
"Entree du regime moteur - panne du circuit",	// P0725
"Entree du regime moteur - probleme de performance/de limites",	// P0726
"Entree du regime moteur - aucun signal",	// P0727
"Entree du regime moteur - circuit intermittent",	// P0728
"Vitesse 6 - rapport incorrect",	// P0729
"Rapport de demultiplication de la vitesse incorrect",	// P0730
"Vitesse 1 - rapport incorrect",	// P0731
"Vitesse 2 - rapport incorrect",	// P0732
"Vitesse 3 - rapport incorrect",	// P0733
"Vitesse 4 - rapport incorrect",	// P0734
"Vitesse 5 - rapport incorrect",	// P0735
"Marche arriere - rapport incorrect",	// P0736
"Regime moteur calculateur de transmission - circuit de sortie",	// P0737
"Regime moteur calculateur de transmission - circuit de sortie faible",	// P0738
"Reference de temps a haute resolution signal B - aucun pulse",	// P0739
"Electrovanne du convertisseur de couple - panne du circuit",	// P0740
"Electrovanne du convertisseur de couple - performance ou blocage",	// P0741
"Electrovanne du convertisseur de couple - blocage",	// P0742
"Electrovanne du convertisseur de couple - electrique",	// P0743
"Electrovanne du convertisseur de couple - circuit intermittent",	// P0744
"Electrovanne du convertisseur de couple - panne du circuit",	// P0745
"Electrovanne du convertisseur de couple - performance ou blocage",	// P0746
"Electrovanne du convertisseur de couple - blocage",	// P0747
"Electrovanne du convertisseur de couple - electrique",	// P0748
"Electrovanne du convertisseur de couple - circuit intermittent",	// P0749
"Electrovanne de changement de vitesse A - panne du circuit",	// P0750
"Electrovanne de changement de vitesse A - performance ou blocage",	// P0751
"Electrovanne de changement de vitesse A - blocage",	// P0752
"Electrovanne de changement de vitesse A - electrique",	// P0753
"Electrovanne de changement de vitesse A - circuit intermittent",	// P0754
"Electrovanne de changement de vitesse B - panne du circuit",	// P0755
"Electrovanne de changement de vitesse B - performance ou blocage",	// P0756
"Electrovanne de changement de vitesse B - blocage",	// P0757
"Electrovanne de changement de vitesse B - electrique",	// P0758
"Electrovanne de changement de vitesse B - circuit intermittent",	// P0759
"Electrovanne de changement de vitesse C - panne du circuit",	// P0760
"Electrovanne de changement de vitesse C - performance ou blocage",	// P0761
"Electrovanne de changement de vitesse C - blocage",	// P0762
"Electrovanne de changement de vitesse C - electrique",	// P0763
"Electrovanne de changement de vitesse C - circuit intermittent",	// P0764
"Electrovanne de changement de vitesse D - panne du circuit",	// P0765
"Electrovanne de changement de vitesse D - performance ou blocage",	// P0766
"Electrovanne de changement de vitesse D - blocage",	// P0767
"Electrovanne de changement de vitesse D - electrique",	// P0768
"Electrovanne de changement de vitesse D - circuit intermittent",	// P0769
"Electrovanne de changement de vitesse E - panne du circuit",	// P0770
"Electrovanne de changement de vitesse E - performance ou blocage",	// P0771
"Electrovanne de changement de vitesse E - blocage",	// P0772
"Electrovanne de changement de vitesse E - electrique",	// P0773
"Electrovanne de changement de vitesse E - circuit intermittent",	// P0774
"Electrovanne de commande de pression B - panne",	// P0775
"Electrovanne de commande de pression B - performance ou blocage",	// P0776
"Electrovanne de commande de pression B - blocage",	// P0777
"Electrovanne de commande de pression B - probleme electrique",	// P0778
"Electrovanne de commande de pression B - circuit intermittent",	// P0779
"Selection de la vitesse - probleme de changement de vitesse",	// P0780
"Selection de la vitesse, 1-2 - probleme de changement de vitesse",	// P0781
"Selection de la vitesse, 2-3 - probleme de changement de vitesse",	// P0782
"Selection de la vitesse, 3-4 - probleme de changement de vitesse",	// P0783
"Selection de la vitesse, 4-5 - probleme de changement de vitesse",	// P0784
"Electrovanne de changement de vitesse - panne du circuit",	// P0785
"Electrovanne de changement de vitesse - probleme de performance/de limites",	// P0786
"Electrovanne de changement de vitesse - basse",	// P0787
"Electrovanne de changement de vitesse - haute",	// P0788
"Electrovanne de changement de vitesse - intermittent",	// P0789
"Commutateur selection de mode de transmission - panne du circuit",	// P0790
"Capteur de vitesse de l'arbre intermediaire de transmission - panne du cicuit",	// P0791
"Capteur de vitesse de l'arbre intermediaire de transmission - probleme de mesure/performance",	// P0792
"Capteur de vitesse de l'arbre intermediaire de transmission - aucun signal",	// P0793
"Capteur de vitesse de l'arbre intermediaire de transmission - panne intermittente du circuit",	// P0794
"Electrovanne de pression d'huile de transmission C - panne du circuit",	// P0795
"Electrovanne de pression d'huile de transmission C - performance ou blocage",	// P0796
"Electrovanne de pression d'huile de transmission C - blocage",	// P0797
"Electrovanne de pression d'huile de transmission C - probleme electrique",	// P0798
"Electrovanne de pression d'huile de transmission C - panne intermittente du circuit",	// P0799
"Systeme de commande de la boite de transfert, commande de lampe temoin d'affichage des defauts - panne",	// P0800
"Circuit de blocage de marche arriere - panne",	// P0801
"Commande de la transmission, commande de lampe temoin d'affichage des defauts - circuit ouvert",	// P0802
"Electrovanne de montee des vitesse 1-4 (saut de vitesses) - panne du circuit",	// P0803
"Lampe temoin de montee des vitesses 1-4 (saut de vitesses) - panne de circuit",	// P0804
"Capteur de la position de la pedale d'embrayage - panne du circuit",	// P0805
"Capteur de la position de la pedale d'embrayage - probleme de mesure/performance",	// P0806
"Capteur de la position de la pedale d'embrayage - valeur d'entree trop basse",	// P0807
"Capteur de la position de la pedale d'embrayage - valeur d'entree trop elevee",	// P0808
"Capteur de la position de la pedale d'embrayage - panne intermittente du circuit",	// P0809
"Erreur de commande de position de la pedale d'embrayage",	// P0810
"Patinage excessif de l'embrayage",	// P0811
"Marche arriere - panne du circuit d'entree",	// P0812
"Marche arriere - panne du circuit de sortie",	// P0813
"Affichage de position du levier de vitesses - panne du circuit",	// P0814
"Contacteur de montee des vitesses - panne du circuit",	// P0815
"Contacteur de descente des vitesses - panne du circuit",	// P0816
"Circuit de mise hors service du demarreur - panne",	// P0817
"Interrupteur de fil d'attaque - panne du circuit",	// P0818
"Correlation entre le contacteur montee/descente des vitesses et la position du levier de vitesses",	// P0819
"Capteur de position X-Y du levier de vitesses - panne du circuit",	// P0820
"Capteur de position X du levier de vitesses - panne du circuit",	// P0821
"Capteur de position Y du levier de vitesses - panne du circuit",	// P0822
"Capteur de position X du levier de vitesses - circuit intermittent",	// P0823
"Capteur de position Y du levier de vitesses - circuit intermittent",	// P0824
"Commutateur a pression et tirage du levier de vitesses - panne du circuit",	// P0825
"Contacteur montee/descente des vitesses - circuit d'entree",	// P0826
"Contacteur montee/descente des vitesses - circuit d'entree trop faible",	// P0827
"Contacteur montee/descente des vitesses - circuit d'entree trop fort",	// P0828
"Montee des vitesses 5-6",	// P0829
"Contacteur de position de la pedale d'embrayage A - panne du circuit",	// P0830
"Contacteur de position de la pedale d'embrayage A - valeur d'entree trop basse",	// P0831
"Contacteur de position de la pedale d'embrayage A - valeur d'entree trop haute",	// P0832
"Contacteur de position de la pedale d'embrayage B - panne du circuit",	// P0833
"Contacteur de position de la pedale d'embrayage B - valeur d'entree trop basse",	// P0834
"Contacteur de position de la pedale d'embrayage B - valeur d'entree trop haute",	// P0835
"Contacteur 4 roues motrices - panne du circuit",	// P0836
"Contacteur 4 roues motrices - probleme de mesure/performance",	// P0837
"Contacteur 4 roues motrices - valeur d'entree trop basse",	// P0838
"Contacteur 4 roues motrices - valeur d'entree trop elevee",	// P0839
"Pressostat/capteur de pression d'huile de transmission A - panne du circuit",	// P0840
"Pressostat/capteur de pression d'huile de transmission A - probleme de mesure/performance",	// P0841
"Pressostat/capteur de pression d'huile de transmission A - valeur d'entree trop basse",	// P0842
"Pressostat/capteur de pression d'huile de transmission A - valeur d'entree trop haute",	// P0843
"Pressostat/capteur de pression d'huile de transmission A - panne intermittente du circuit",	// P0844
"Pressostat/capteur de pression d'huile de transmission B - panne du circuit",	// P0845
"Pressostat/capteur de pression d'huile de transmission B - probleme de mesure/performance",	// P0846
"Pressostat/capteur de pression d'huile de transmission B - valeur d'entree trop basse",	// P0847
"Pressostat/capteur de pression d'huile de transmission B - valeur d'entree trop haute",	// P0848
"Pressostat/capteur de pression d'huile de transmission B - panne intermittente du circuit",	// P0849
"Contacteur de position Neutre/parking - panne du circuit d'entree",	// P0850
"Contacteur de position Neutre/Parking - circuit d'entree trop faible",	// P0851
"Contacteur de position Neutre/Parking - circuit d'entree trop fort",	// P0852
"Contacteur de position Drive - panne du circuit d'entree",	// P0853
"Contacteur de position Drive - circuit d'entree trop faible",	// P0854
"Contacteur de position Drive - circuit d'entree trop fort",	// P0855
"Signal d'entree anti-patinage - panne",	// P0856
"Signal d'entree anti-patinage - proleme de mesure/performance",	// P0857
"Signal d'entree anti-patinage - faible",	// P0858
"Signal d'entree anti-patinage - haut",	// P0859
"Circuit de communication du boitier electronique de changement de vitesses - panne",	// P0860
"Circuit de communication du boitier electronique de changement de vitesses - valeur d'entree trop basse",	// P0861
"Circuit de communication du boitier electronique de changement de vitesses - valeur d'entree trop haute",	// P0862
"Circuit de communication du calculateur de transmission - panne",	// P0863
"Circuit de communication du calculateur de transmission - probleme de mesure/performance",	// P0864
"Circuit de communication du calculateur de transmission - valeur d'entree trop basse",	// P0865
"Circuit de communication du calculateur de transmission - valeur d'entree trop haute",	// P0866
"Capteur de pression d'huile de transmission",	// P0867
"Capteur de pression d'huile de transmission - faible",	// P0868
"Capteur de pression d'huile de transmission - haut",	// P0869
"Capteur de pression d'huile de transmission C - panne du circuit",	// P0870
"Capteur de pression d'huile de transmission C - plage de mesure/performance",	// P0871
"Capteur de pression d'huile de transmission C - circuit trop bas",	// P0872
"Capteur de pression d'huile de transmission C - circuit trop haut",	// P0873
"Capteur de pression d'huile de transmission C - panne intermittente du circuit",	// P0874
"Dapteur de pression d'huile de transmission D - panne du circuit",	// P0875
"Dapteur de pression d'huile de transmission D - plage de mesure/performance",	// P0876
"Dapteur de pression d'huile de transmission D - circuit trop bas",	// P0877
"Dapteur de pression d'huile de transmission D - circuit trop haut",	// P0878
"Dapteur de pression d'huile de transmission D - panne intermittente du circuit",	// P0879
"Calculateur de transmission - panne du signal d'entree de l'amimentation electrique",	// P0880
"Calculateur de transmission - plage de mesure/performance du signal d'entree de l'amimentation electrique",	// P0881
"Calculateur de transmission - signal d'entree de l'amimentation electrique trop faible",	// P0882
"Calculateur de transmission - signal d'entree de l'amimentation electrique trop fort",	// P0883
"Calculateur de transmission - panne intermittente du signal d'entree de l'amimentation electrique",	// P0884
"Relais d'alimentation electrique du calculateur de transmission - circuit de commande ouvert",	// P0885
"Relais d'alimentation electrique du calculateur de transmission - circuit de commande trop faible",	// P0886
"Relais d'alimentation electrique du calculateur de transmission - circuit de commande trop fort",	// P0887
"Relais d'alimentation electrique du calculateur de transmission - panne du circuit de sondage",	// P0888
"Relais d'alimentation electrique du calculateur de transmission - plage de mesure/performance du circuit de sondage",	// P0889
"Relais d'alimentation electrique du calculateur de transmission - circuit de sondage trop faible",	// P0890
"Relais d'alimentation electrique du calculateur de transmission - circuit de sondage trop fort",	// P0891
"Relais d'alimentation electrique du calculateur de transmission - panne intermittente du circuit de sondage",	// P0892
"Plusieurs vitesses engagees",	// P0893
"Patinage d'un composant de la transmission",	// P0894
"Duree de changement de vitesse trop courte",	// P0895
"Duree de changement de vitesse trop longue",	// P0896
"Huile de transmission degradee",	// P0897
"Commande de transmission - commande de lampe temoin d'affichage des defauts - circuit trop bas",	// P0898
"Commande de transmission - commande de lampe temoin d'affichage des defauts - circuit trop haut",	// P0899
"Capteur d'embrayage - circuit ouvert",	// P0900
"Capteur d'embrayage - plage de msure/performance du circuit",	// P0901
"Capteur d'embrayage - circuit trop bas",	// P0902
"Capteur d'embrayage - circuit trop haut",	// P0903
"Circuit de selection de coulisse de transmission - panne",	// P0904
"Circuit de selection de coulisse de transmission - plage de mesure/performance",	// P0905
"Circuit de selection de coulisse de transmission - basse",	// P0906
"Circuit de selection de coulisse de transmission - haute",	// P0907
"Circuit de selection de coulisse de transmission - panne intermittente du circuit",	// P0908
"Erreur de commande de selection de coulisse de transmission",	// P0909
"Capteur de selection de coulisse de transmission - circuit ouvert",	// P0910
"Capteur de selection de coulisse de transmission - plage de mesure/performance",	// P0911
"Capteur de selection de coulisse de transmission - circuit trop bas",	// P0912
"Capteur de selection de coulisse de transmission - circuit trop haut",	// P0913
"Circuit de position de changement de vitesses - panne",	// P0914
"Circuit de position de changement de vitesses - plage de mesure/performance",	// P0915
"Circuit de position de changement de vitesses - basse",	// P0916
"Circuit de position de changement de vitesses - haute",	// P0917
"Circuit de position de changement de vitesses - panne intermittente",	// P0918
"Commande de position de changement de vitesses - erreur",	// P0919
"Capteur de changement de vitesses vers l'avant - circuit ouvert",	// P0920
"Capteur de changement de vitesses vers l'avant - plage de mesure/performance",	// P0921
"Capteur de changement de vitesses vers l'avant - circuit trop bas",	// P0922
"Capteur de changement de vitesses vers l'avant - circuit trop haut",	// P0923
"Capteur de changement de vitesses vers l'arriere - circuit ouvert",	// P0924
"Capteur de changement de vitesses vers l'arriere - plage de mesure/performance",	// P0925
"Capteur de changement de vitesses vers l'arriere - circuit trop bas",	// P0926
"Capteur de changement de vitesses vers l'arriere - circuit trop haut",	// P0927
"Electrovanne de blocage de changement de vitesse - circuit ouvert",	// P0928
"Electrovanne de blocage de changement de vitesse - plage de mesure/performance du circuit",	// P0929
"Electrovanne de blocage de changement de vitesse - circuit trop bas",	// P0930
"Electrovanne de blocage de changement de vitesse - circuit trop haut",	// P0931
"Capteur de pression hydraulique - panne du circuit",	// P0932
"Capteur de pression hydraulique - plage de mesure/performance du circuit",	// P0933
"Capteur de pression hydraulique - signal d'entree du circuit trop bas",	// P0934
"Capteur de pression hydraulique - signal d'entree du circuit trop haut",	// P0935
"Capteur de pression hydraulique - circuit intermittent",	// P0936
"Sonde de temperature du fluide hydraulique - panne du circuit",	// P0937
"Sonde de temperature du fluide hydraulique - plage de mesure/performance",	// P0938
"Sonde de temperature du fluide hydraulique - signal d'entree du circuit trop bas",	// P0939
"Sonde de temperature du fluide hydraulique - signal d'entree du circuit trop haut",	// P0940
"Sonde de temperature du fluide hydraulique - circuit intermittent",	// P0941
"Module de pression hydraulique",	// P0942
"Module de pression hydraulique - duree de cycle trop courte",	// P0943
"Module de pression hydraulique - perte de pression",	// P0944
"Relais de la pompe hydraulique - circuit ouvert",	// P0945
"Relais de la pompe hydraulique - plage de mesure/performance du circuit",	// P0946
"Relais de la pompe hydraulique - circuit trop bas",	// P0947
"Relais de la pompe hydraulique - circuit trop haut",	// P0948
"Boite de vitesse a passage automatique - apprentissage adaptatif non effectue",	// P0949
"Circuit de commande boite de vitesses a passage automatique",	// P0950
"Circuit de commande boite de vitesses a passage automatique - plage de mesure/performance",	// P0951
"Circuit de commande boite de vitesses a passage automatique - basse",	// P0952
"Circuit de commande boite de vitesses a passage automatique - haute",	// P0953
"Circuit de commande boite de vitesses a passage automatique - panne intermittente du circuit",	// P0954
"Circuit de programme boite de vitesses a passage automatique - panne",	// P0955
"Circuit de programme boite de vitesses a passage automatique - plage de mesure/performance",	// P0956
"Circuit de programme boite de vitesses a passage automatique - basse",	// P0957
"Circuit de programme boite de vitesses a passage automatique - haute",	// P0958
"Circuit de programme boite de vitesses a passage automatique - panne intermittente du circuit",	// P0959
"Electrovanne de regulation de pression A - circuit de commande ouvert",	// P0960
"Electrovanne de regulation de pression A - plage de mesure/performance du circuit de commande",	// P0961
"Electrovanne de regulation de pression A - circuit de commande trop faible",	// P0962
"Electrovanne de regulation de pression A - circuit de commande trop fort",	// P0963
"Electrovanne de regulation de pression B - circuit de commande ouvert",	// P0964
"Electrovanne de regulation de pression B - plage de mesure/performance du circuit de commande",	// P0965
"Electrovanne de regulation de pression B - circuit de commande trop faible",	// P0966
"Electrovanne de regulation de pression B - circuit de commande trop fort",	// P0967
"Electrovanne de regulation de pression C - circuit de commande ouvert",	// P0968
"Electrovanne de regulation de pression C - plage de mesure/performance du circuit de commande",	// P0969
"Electrovanne de regulation de pression C - circuit de commande trop faible",	// P0970
"Electrovanne de regulation de pression C - circuit de commande trop fort",	// P0971
"Electrovanne de changement de vitesse A - plage de mesure/performance du circuit de commande",	// P0972
"Electrovanne de changement de vitesse A - circuit de commande trop faible",	// P0973
"Electrovanne de changement de vitesse A - circuit de commande trop fort",	// P0974
"Electrovanne de changement de vitesse B - plage de mesure/performance du circuit de commande",	// P0975
"Electrovanne de changement de vitesse B - circuit de commande trop faible",	// P0976
"Electrovanne de changement de vitesse B - circuit de commande trop fort",	// P0977
"Electrovanne de changement de vitesse C - plage de mesure/performance du circuit de commande",	// P0978
"Electrovanne de changement de vitesse C - circuit de commande trop faible",	// P0979
"Electrovanne de changement de vitesse C - circuit de commande trop fort",	// P0980
"Electrovanne de changement de vitesse D - plage de mesure/performance du circuit de commande",	// P0981
"Electrovanne de changement de vitesse D - circuit de commande trop faible",	// P0982
"Electrovanne de changement de vitesse D - circuit de commande trop fort",	// P0983
"Electrovanne de changement de vitesse E - plage de mesure/performance du circuit de commande",	// P0984
"Electrovanne de changement de vitesse E - circuit de commande trop faible",	// P0985
"Electrovanne de changement de vitesse E - circuit de commande trop fort",	// P0986
"Capteur de pression d'huile de transmission E - panne du circuit",	// P0987
"Capteur de pression d'huile de transmission E - plage de mesure/performance du circuit",	// P0988
"Capteur de pression d'huile de transmission E - circuit trop bas",	// P0989
"Capteur de pression d'huile de transmission E - circuit trop haut",	// P0990
"Capteur de pression d'huile de transmission E - circuit intermittent",	// P0991
"Capteur de pression d'huile de transmission F - panne du circuit",	// P0992
"Capteur de pression d'huile de transmission F - plage de mesure/performance du circuit",	// P0993
"Capteur de pression d'huile de transmission F - circuit trop bas",	// P0994
"Capteur de pression d'huile de transmission F - circuit trop haut",	// P0995
"Capteur de pression d'huile de transmission F - circuit intermittent",	// P0996
"Electrovanne de changement de vitesse F - plage de mesure/performance du circuit de commande",	// P0997
"Electrovanne de changement de vitesse F - circuit de commande trop faible",	// P0998
"Electrovanne de changement de vitesse F - circuit de commande trop fort"	// P0999
};
