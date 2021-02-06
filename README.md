# Huy_Jin_TP4

Apache signale de nombreuses données sur votre site web, votre serveur et vos utilisateurs, mais l'astuce consiste à extraire ces données des journaux. 
L'analyse des journaux Apache convertit le texte brut produit par Apache en champs qui peuvent être indexés, recherchés et analysés. 
Il est ainsi plus facile de superviser Apache, d'analyser des problèmes spécifiques ou d'examiner des tendances plus générales.

Cette section montre comment analyser les journaux d'Apache à l'aide d'outils de ligne de commande courants, ainsi que des solutions de gestion des journaux. 
Lors de la démonstration de ces solutions, nous utiliserons l'exemple de l'analyse du code d'état HTTP (500) du message de journal suivant :
192.168.0.1 - - [08/Sep/2012:11:15:00 +0200] "GET /page2.html HTTP/1.1" 200 2000 "http://intranet-if.insa-lyon.fr/page1.html" "Mozilla/5.0"
