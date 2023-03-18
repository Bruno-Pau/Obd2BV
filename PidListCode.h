// Liste des intitules de PID
#define NBPIDMOD1 129
#define NBPIDMOD5 16
#define NBPIDMOD6 256
#define NBPIDMOD9 16
typedef char INTITUL[100];

char szItemMode1[NBPIDMOD1][100] = {
"Liste des PIDs supportes (plage de 01 a 32)",	// 0
"Status depuis le dernier effacement des codes defauts",	// 1
"Code defaut qui a provoque l'enregistrement de donnees gelees",	// 2
"Etat du circuit de carburant",	// 3
"Charge moteur calculee en %",	// 4
"Temperature du liquide de refroidissement moteur en °C",	// 5
"Ajustement a court terme du carburant voie 1 en %",	// 6
"Ajustement a long terme du carburant voie 1en %",	// 7
"Ajustement a court terme du carburant voie2 en %",	// 8
"Ajustement a long terme du carburant voie 2 en %",	// 9
"Pression de carburant en kPa",	// 10
"Pression d'admission absolue en kPa",	// 11
"Regime moteur en tours/min",	// 12
"Vitesse du vehicule en km/h",	// 13
"Avance a l'allumage sur le cylindre 1 en degre",	// 14
"Temperature d'air d'admission en °C",	// 15
"Debit d'air mesure par le debimetre en g/s",	// 16
"Position absolue du papillon des gaz en %",	// 17
"Etat du circuit secondaire d'admission",	// 18
"Capteur d'02 positions voie/capteur",	// 19
"Tension du capteur d'02 voie 1 capteur 1",	// 20
"Tension du capteur d'02 voie 1 capteur 2",	// 21
"Tension du capteur d'02 voie 1 capteur 3",	// 22
"Tension du capteur d'02 voie 1 capteur 4",	// 23
"Tension du capteur d'02 voie2 capteur 1",	// 24
"Tension du capteur d'02 voie2 capteur 2",	// 25
"Tension du capteur d'02 voie2 capteur 3",	// 26
"Tension du capteur d'02 voie2 capteur 4",	// 27
"Specification OBD du calculateur",	// 28
"Capteur d'02 positions voie/capteur",	// 29
"Etat des entrees auxilliaires",	// 30
"Duree depuis le demarrage du moteur",	// 31
"Liste des PIDs supportes (plage de33 a 64)",	// 32
"Distance effectuee depuis que la MIL est allumee en kms",	// 33
"Pression relative de carburant dans la rampe d'injection en kPa",	// 34
"Pression de carburant dans la rampe d'injection en kPa",	// 35
"Capteur d'O2 (plage etendue) voie 1, capteur 1 (lambda et tension)",	// 36
"Capteur d'O2 (plage etendue) voie 1, capteur2 (lambda et tension)",	// 37
"Capteur d'O2 (plage etendue) voie 1, capteur3 (lambda et tension)",	// 38
"Capteur d'O2 (plage etendue) voie 1, capteur4 (lambda et tension)",	// 39
"Capteur d'O2 (plage etendue) voie 2, capteur 1 (lambda et tension)",	// 40
"Capteur d'O2 (plage etendue) voie 2, capteur2 (lambda et tension)",	// 41
"Capteur d'O2 (plage etendue) voie 2, capteur3 (lambda et tension)",	// 42
"Capteur d'O2 (plage etendue) voie 2, capteur4 (lambda et tension)",	// 43
"Consigne de l'EGR en %",	// 44
"Erreur sur la consigne de l'EGR en %",	// 45
"Consigne de la purge d'evaporation en %",	// 46
"Niveau de carburant en %",	// 47
"Nombre d'avertissement(s) depuis que les defauts (DTC)ont ete effaces",	// 48
"Distance parcourue depuis que les defauts (DTC) ont ete effaces.",	// 49
"Pression des vapeurs du systeme d'evaporation en Pa",	// 50
"Pression atmospherique en kPa",	// 51
"Capteur d'O2 (plage etendue) voie 1, capteur 1 (lambda et tension)",	// 52
"Capteur d'O2 (plage etendue) voie 1, capteur2 (lambda et tension)",	// 53
"Capteur d'O2 (plage etendue) voie 1, capteur3 (lambda et tension)",	// 54
"Capteur d'O2 (plage etendue) voie 1, capteur4 (lambda et tension)",	// 55
"Capteur d'O2 (plage etendue) voie 2, capteur 1 (lambda et tension)",	// 56
"Capteur d'O2 (plage etendue) voie 2, capteur2 (lambda et tension)",	// 57
"Capteur d'O2 (plage etendue) voie 2, capteur3 (lambda et tension)",	// 58
"Capteur d'O2 (plage etendue) voie 2, capteur4 (lambda et tension)",	// 59
"Temperature du catalyseur en °C. voie 1, capteur 1",	// 60
"Temperature du catalyseur en °C. voie 2, capteur 1",	// 61
"Temperature du catalyseur en °C. voie 1, capteur 2",	// 62
"Temperature du catalyseur en °C. voie 2, capteur 2",	// 63
"Liste des PIDs supportes (plage de65 a 96)",	// 64
"Etat des grandeurs surveillees pendant ce cycle de conduite",	// 65
"Tension du module de contrôle en V",	// 66
"Charge moteur absolue",	// 67
"Consigne equivalente du ratio carburant/air",	// 68
"Position relative du papillon des gaz en %",	// 69
"Temperature d'air ambiante en °C",	// 70
"Position absolue du papillon des gaz B en %",	// 71
"Position absolue du papillon des gaz C en %",	// 72
"Position de la pedale d'accelerateur D en %",	// 73
"Position de la pedale d'accelerateur E en %",	// 74
"Position de la pedale d'accelerateur F en %",	// 75
"Consigne de l'actuateur de papillon des gaz en %",	// 76
"Duree de fonctionnement du moteur depuis que la MIL est allumee en min",	// 77
"Duree de fonctionnement du moteur depuis que les defauts ont ete effacee en min",	// 78
"Information de configuration de l'equipement de test externe n°1",	// 79
"Information de configuration de l'equipement de test externe n°2",	// 80
"Type du carburant actuellement utilise par le vehicule",	// 81
"Pourcentage d'alcool dans le carburant en %",	// 82
"Pression absolue des vapeurs dans le systeme d'evaporation en kPa",	// 83
"Pression des vapeurs dans le systeme d'evaporationen Pa",	// 84
"Compensation a court terme du capteur O2 voie 1 et 3",	// 85
"Compensation a long terme du capteur O2 voie 1 et 3",	// 86
"Compensation a court terme du capteur O2 voie 2 et 4",	// 87
"Compensation a long terme du capteur O2 voie 2 et 4",	// 88
"Pression absolue de la rampe de carburant en kPa",	// 89
"Position relative de la pedale d'accelerateur en %",	// 90
"Duree de vie restante du bloc de batterie (hybride) en %",	// 91
"Temperature d'huile moteur en °C",	// 92
"Avance de l'injection de carburant en °",	// 93
"Consommation de carburant en litre/h",	// 94
"Legislation d'emission auquel ce vehicule repond",	// 95
"Liste des PIDs supportes (plage de97 a 128)",	// 96
"Demande du conducteur : pourcentage de couple (%)",	// 97
"Pourcentage de couple final du moteur (%)",	// 98
"Reference de couple du moteur en Nm",	// 99
"Donnee de couple moteur en %",	// 100
"Entrees / sorties auxilliaires",	// 101
"Capteur de debimetre",	// 102
"Temperature(s) d'eau moteur en °C",	// 103
"Capteur(s) de temperature d'air en °C",	// 104
"Consigne d'EGR et erreur EGR",	// 105
"Consigne du contrôle d'entree d'air et position relative d'entree d'air",	// 106
"Temperature(s) des gaz de recirculation en °C",	// 107
"Consigne de l'actuateur de contrôle du papillon des gaz et position relative du papillon",	// 108
"Systeme de contrôle de la pression de carburant",	// 109
"Systeme de contrôle de la pression d'injection",	// 110
"Pression d'entree du turbo compresseur en kPa",	// 111
"Contrôle de la pression du boost en kPa",	// 112
"Contrôle du turbo a geometrie variable (VGT)",	// 113
"Contrôle de la valve de decharge (wastegate)",	// 114
"Pression a l'echappement en kPa",	// 115
"Regime du/des turbo(s) en tr/min",	// 116
"Temperature du turbo A en °C",	// 117
"Temperature du turbo B en °C",	// 118
"Temperature de l'echangeur d'air en °C",	// 119
"Temperature des gaz d'echappement voie 1en °C",	// 120
"Temperature des gaz d'echappement voie 2 en °C",	// 121
"Filtre a particule diesel voie 1",	// 122
"Filtre a particule diesel voie 2",	// 123
"Temperature du filtre a particule diesel",	// 124
"Etat du contrôle d'etendu des Nox NTE",	// 125
"Etat du contrôle d'etendu des PM NTE",	// 126
"Duree de fonctionnement moteur",	// 127
"Liste des PIDs supportes (plage de129 a 160)"	// 128
};	// 

char szItemMode5[NBPIDMOD5][100] = {
"Liste des PIDs supportes (plage de 01 a 32)",	// 0
"Tension de seuil du capteur de riche a pauvre",	// 1
"Tension de seuile du capteur de pauvre a riche",	// 2
"Tension basse utilisee pour le calcul du temps de passage",	// 3
"Tensionhaute utilisee pour le calcul du temps de passage",	// 4
"Temps de passage de riche a pauvre calcule",	// 5
"Temps de passage de pauvre a riche calcule",	// 6
"Tension minimun du capteur pendant le cycle de test",	// 7
"Tension maximun du capteur pendant le cycle de test",	// 8
"Temps entre les transitions du capteur",	// 9
"Periode du capteur",	// 10
"Reserve pour utilisation future"	// 11
};	

char szItemMode6[NBPIDMOD6][100] = {
"Determination des PIDs supporte (plage de 01h a 20h)",	// 0
"Capteur des gaz d'echappement voie 1 - capteur 1",	// 1
"Capteur des gaz d'echappement voie 1 - capteur 2",	// 2
"Capteur des gaz d'echappement voie 1 - capteur 3",	// 3
"Capteur des gaz d'echappement voie 1 - capteur 4",	// 4
"Capteur des gaz d'echappement voie 2 - capteur 1",	// 5
"Capteur des gaz d'echappement voie 2 - capteur 2",	// 6
"Capteur des gaz d'echappement voie 2 - capteur 3",	// 7
"Capteur des gaz d'echappement voie 2 - capteur 4",	// 8
"Capteur des gaz d'echappement voie 3 - capteur 1",	// 9
"Capteur des gaz d'echappement voie 3 - capteur 2",	// 10
"Capteur des gaz d'echappement voie 3 - capteur 3",	// 11
"Capteur des gaz d'echappement voie 3 - capteur 4",	// 12
"Capteur des gaz d'echappement voie 4 - capteur 1",	// 13
"Capteur des gaz d'echappement voie 4 - capteur 2",	// 14
"Capteur des gaz d'echappement voie 4 - capteur 3",	// 15
"Capteur des gaz d'echappement voie 4 - capteur 4",	// 16
"Reserve pour utilisation future",	// 17
"Reserve pour utilisation future",	// 18
"Reserve pour utilisation future",	// 19
"Reserve pour utilisation future",	// 20
"Reserve pour utilisation future",	// 21
"Reserve pour utilisation future",	// 22
"Reserve pour utilisation future",	// 23
"Reserve pour utilisation future",	// 24
"Reserve pour utilisation future",	// 25
"Reserve pour utilisation future",	// 26
"Reserve pour utilisation future",	// 27
"Reserve pour utilisation future",	// 28
"Reserve pour utilisation future",	// 29
"Reserve pour utilisation future",	// 30
"Reserve pour utilisation future",	// 31
"Determination des PIDs supporte (plage de 21h a 40h)",	// 32
"Catalytique voie 1",	// 33
"Catalytique voie 2",	// 34
"Catalytique voie 3",	// 35
"Catalytique voie 4",	// 36
"Reserve pour utilisation future",	// 37
"Reserve pour utilisation future",	// 38
"Reserve pour utilisation future",	// 39
"Reserve pour utilisation future",	// 40
"Reserve pour utilisation future",	// 41
"Reserve pour utilisation future",	// 42
"EGR voie 1",	// 49
"EGR voie 2",	// 50
"EGR voie 3",	// 51
"EGR voie 4",	// 52
"VVT voie 1",	// 53
"VVT voie 2",	// 54
"VVT voie 3",	// 55
"VVT voie 4",	// 56
"EVAP (Cap Off / 0.150”)",	// 57
"EVAP (0.090“)",	// 58
"EVAP (0.040”)",	// 59
"EVAP (0.020“)",	// 60
"Flux de purge",	// 61
"Reserve pour utilisation future",	// 62
"Reserve pour utilisation future",	// 63
"Determination des PIDs supporte (plage de 41h a 60h)",	// 64
"Capteur des gaz d'echappement chauffe voie 1 - capteur 1",	// 65
"Capteur des gaz d'echappement chauffe voie 1 - capteur 2",	// 66
"Capteur des gaz d'echappement chauffe voie 1 - capteur 3",	// 67
"Capteur des gaz d'echappement chauffe voie 1 - capteur 4",	// 68
"Capteur des gaz d'echappement chauffe voie 2 - capteur 1",	// 69
"Capteur des gaz d'echappement chauffe voie 2 - capteur 2",	// 70
"Capteur des gaz d'echappement chauffe voie 2 - capteur 3",	// 71
"Capteur des gaz d'echappement chauffe voie 2 - capteur 4",	// 72
"Capteur des gaz d'echappement chauffe voie 3 - capteur 1",	// 73
"Capteur des gaz d'echappement chauffe voie 3 - capteur 2",	// 74
"Capteur des gaz d'echappement chauffe voie 3 - capteur 3",	// 75
"Capteur des gaz d'echappement chauffe voie 3 - capteur 4",	// 76
"Capteur des gaz d'echappement chauffe voie 4 - capteur 1",	// 77
"Capteur des gaz d'echappement chauffe voie 4 - capteur 2",	// 78
"Capteur des gaz d'echappement chauffe voie 4 - capteur 3",	// 79
"Capteur des gaz d'echappement chauffe voie 4 - capteur 4",	// 80
"Reserve pour utilisation future",	// 81
"Reserve pour utilisation future",	// 82
"Reserve pour utilisation future",	// 83
"Reserve pour utilisation future",	// 84
"Reserve pour utilisation future",	// 85
"Reserve pour utilisation future",	// 86
"Reserve pour utilisation future",	// 87
"Reserve pour utilisation future",	// 88
"Reserve pour utilisation future",	// 89
"Reserve pour utilisation future",	// 90
"Reserve pour utilisation future",	// 91
"Reserve pour utilisation future",	// 92
"Reserve pour utilisation future",	// 93
"Reserve pour utilisation future",	// 94
"Reserve pour utilisation future",	// 95
"Determination des PIDs supporte (plage de 61h a 80h)",	// 96
"Catalyseur chauffe voie 1",	// 97
"Catalyseur chauffe voie 2",	// 98
"Catalyseur chauffe voie 3",	// 99
"Catalyseur chauffe voie 4",	// 100
"Reserve pour utilisation future",	// 101
"Reserve pour utilisation future",	// 102
"Reserve pour utilisation future",	// 103
"Reserve pour utilisation future",	// 104
"Reserve pour utilisation future",	// 105
"Reserve pour utilisation future",	// 106
"Reserve pour utilisation future",	// 107
"Reserve pour utilisation future",	// 108
"Reserve pour utilisation future",	// 109
"Reserve pour utilisation future",	// 110
"Reserve pour utilisation future",	// 111
"Reserve pour utilisation future",	// 112
"Air secondaire 1",	// 113
"Air secondaire 2",	// 114
"Air secondaire 3",	// 115
"Air secondaire 4",	// 116
"Reserve pour utilisation future",	// 117
"Reserve pour utilisation future",	// 118
"Reserve pour utilisation future",	// 119
"Reserve pour utilisation future",	// 120
"Reserve pour utilisation future",	// 121
"Reserve pour utilisation future",	// 122
"Reserve pour utilisation future",	// 123
"Reserve pour utilisation future",	// 124
"Reserve pour utilisation future",	// 125
"Reserve pour utilisation future",	// 126
"Reserve pour utilisation future",	// 127
"Determination des PIDs supporte (plage de 81h a A0h)",	// 128
"Systeme de carburant voie 1",	// 129
"Systeme de carburant voie 2",	// 130
"Systeme de carburant voie 3",	// 131
"Systeme de carburant voie 4",	// 132
"Pression de turbo voie 1",	// 133
"Pression de turbo voie 2",	// 134
"Reserve pour utilisation future",	// 135
"Reserve pour utilisation future",	// 136
"Reserve pour utilisation future",	// 137
"Reserve pour utilisation future",	// 138
"Reserve pour utilisation future",	// 139
"Reserve pour utilisation future",	// 140
"Reserve pour utilisation future",	// 141
"Reserve pour utilisation future",	// 142
"Reserve pour utilisation future",	// 143
"Absorbeur de Nox voie 1",	// 144
"Absorbeur de Nox voie 2",	// 145
"Reserve pour utilisation future",	// 146
"Reserve pour utilisation future",	// 147
"Reserve pour utilisation future",	// 148
"Reserve pour utilisation future",	// 149
"Reserve pour utilisation future",	// 150
"Reserve pour utilisation future",	// 151
"Catalytique NOx voie 1",	// 152
"Catalytique NOx voie 2",	// 153
"Reserve pour utilisation future",	// 154
"Reserve pour utilisation future",	// 155
"Reserve pour utilisation future",	// 156
"Reserve pour utilisation future",	// 157
"Reserve pour utilisation future",	// 158
"Reserve pour utilisation future",	// 159
"Determination des PIDs supporte (plage de A1h a C0h)",	// 160
"Donnees de surveillance generales des rates d'allumage",	// 161
"Donnees des rates d'allumage cylindre 1",	// 162
"Donnees des rates d'allumage cylindre 2",	// 163
"Donnees des rates d'allumage cylindre 3",	// 164
"Donnees des rates d'allumage cylindre 4",	// 165
"Donnees des rates d'allumage cylindre 5",	// 166
"Donnees des rates d'allumage cylindre 6",	// 167
"Donnees des rates d'allumage cylindre 7",	// 168
"Donnees des rates d'allumage cylindre 8",	// 169
"Donnees des rates d'allumage cylindre 9",	// 170
"Donnees des rates d'allumage cylindre 10",	// 171
"Donnees des rates d'allumage cylindre 11",	// 172
"Donnees des rates d'allumage cylindre 12",	// 173
"Donnees des rates d'allumage cylindre 13",	// 174
"Donnees des rates d'allumage cylindre 14",	// 175
"Donnees des rates d'allumage cylindre 15",	// 176
"Donnees des rates d'allumage cylindre 16",	// 177
"Filtre PM voie 1",	// 178
"Filtre PM voie 2",	// 179
"Reserve pour utilisation future",	// 180
"Reserve pour utilisation future",	// 181
"Reserve pour utilisation future",	// 182
"Reserve pour utilisation future",	// 183
"Reserve pour utilisation future",	// 184
"Reserve pour utilisation future",	// 185
"Reserve pour utilisation future",	// 186
"Reserve pour utilisation future",	// 187
"Reserve pour utilisation future",	// 188
"Reserve pour utilisation future",	// 189
"Reserve pour utilisation future",	// 190
"Reserve pour utilisation future",	// 191
"Determination des PIDs supporte (plage de C1h a E0h)",	// 192
"Reserve pour utilisation future",	// 193
"Reserve pour utilisation future",	// 194
"Reserve pour utilisation future",	// 195
"Reserve pour utilisation future",	// 196
"Reserve pour utilisation future",	// 197
"Reserve pour utilisation future",	// 198
"Reserve pour utilisation future",	// 199
"Reserve pour utilisation future",	// 200
"Reserve pour utilisation future",	// 201
"Reserve pour utilisation future",	// 202
"Reserve pour utilisation future",	// 203
"Reserve pour utilisation future",	// 204
"Reserve pour utilisation future",	// 205
"Reserve pour utilisation future",	// 206
"Reserve pour utilisation future",	// 207
"Reserve pour utilisation future",	// 208
"Reserve pour utilisation future",	// 209
"Reserve pour utilisation future",	// 210
"Reserve pour utilisation future",	// 211
"Reserve pour utilisation future",	// 212
"Reserve pour utilisation future",	// 213
"Reserve pour utilisation future",	// 214
"Reserve pour utilisation future",	// 215
"Reserve pour utilisation future",	// 216
"Reserve pour utilisation future",	// 217
"Reserve pour utilisation future",	// 218
"Reserve pour utilisation future",	// 219
"Reserve pour utilisation future",	// 220
"Reserve pour utilisation future",	// 221
"Reserve pour utilisation future",	// 222
"Reserve pour utilisation future",	// 223
"Determination des PIDs supporte (plage de E1h a FFh)",	// 224
"Specifique constructeur",	// 225
"Specifique constructeur",	// 226
"Specifique constructeur",	// 227
"Specifique constructeur",	// 228
"Specifique constructeur",	// 229
"Specifique constructeur",	// 230
"Specifique constructeur",	// 231
"Specifique constructeur",	// 232
"Specifique constructeur",	// 233
"Specifique constructeur",	// 234
"Specifique constructeur",	// 235
"Specifique constructeur",	// 236
"Specifique constructeur",	// 237
"Specifique constructeur",	// 238
"Specifique constructeur",	// 239
"Specifique constructeur",	// 240
"Specifique constructeur",	// 241
"Specifique constructeur",	// 242
"Specifique constructeur",	// 243
"Specifique constructeur",	// 244
"Specifique constructeur",	// 245
"Specifique constructeur",	// 246
"Specifique constructeur",	// 247
"Specifique constructeur",	// 248
"Specifique constructeur",	// 249
"Specifique constructeur",	// 250
"Specifique constructeur",	// 251
"Specifique constructeur",	// 252
"Specifique constructeur",	// 253
"Specifique constructeur",	// 254
"Specifique constructeur"	// 255
};	
	// 
char szItemMode9[NBPIDMOD9][100] = {
"Determination des PIDs supportes (plage de 01h a 20h)",	// 0
"Nb de messages pour le VIN",	// 1
"Numero d'identification du vehicule (VIN)",	// 2
"Nb de messages pour les calibrations",	// 3
"Identificateurs de calibration",	// 4
"Nombre de message pour les verificateurs de CALIB",	// 5
"Numero de verification de calibration",	// 6
"Nb de messages pour les IPT",	// 7
"En utilisation surveillance de performance (IPT)",	// 8
"Nb de messages pour le nom d'ECU",	// 9
"Nom de l'ECU",	// 10
"En utilisation surveillance de performance",	// 11
"Reserve pour utilisation future",	// 12
"Reserve pour utilisation future",	// 13
"Reserve pour utilisation future"	// 14
};
