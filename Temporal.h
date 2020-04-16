

	if(wifiData.substring(0,6) == "_rSev[")
	{
		int _Escn=wifiData.substring(6).toInt();
		String _Temp="";
		
		_Temp=String(_Escn) + " = " + escenario.Ambientes[_Escn].nombre + ":\n";
		_Temp=_Temp + "t0 = " + escenario.Ambientes[_Escn].t0 + ":\n";
		_Temp=_Temp + "t1 = " + escenario.Ambientes[_Escn].t1 + ":\n";
		_Temp=_Temp + "Dias = " + escenario.Ambientes[_Escn].repetir + ":\n";
		_Temp=_Temp + "TBD = " + escenario.Ambientes[_Escn].repetirAlt + ":\n";
		_Temp=_Temp + "Status = " + escenario.Ambientes[_Escn].habilitar + ":\n";

		wifiEnviarln("_rSev OK;");
		cmdOk=1;
	}