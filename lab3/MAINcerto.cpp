   int x;
    while(x!=0) {
        cout << "Deseja armazenar um resistor\n";
        cin >> x;
        if (x!=0) {
            string name;
            double res;
            int lig[2];
            cin >> name >> res >> lig[0] >> lig[1];
            Resistor R(resID,name,res,lig);
            resArray[(resID)] = R;
            resID++;
            R.print();
        }
    }
	
	while(x<resID) {
        resArray[x].print();
        x++;
    }
    
	system("PAUSE");



	


