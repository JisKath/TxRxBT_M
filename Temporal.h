
                if (cmdActivo.equals("ScanSta")) {
                    if (Step == 0) {
                        CmdSnd = false;
                        BufferInFlag = false;
                        BufferInW = "";
                        altoTest = false;
                        Step = 1;
                    }

                    if (Step == 1) {

                        dispSta = 2;

                        if (names_D.get(indice).length() > 4) {

                            if (triggerRcvn) {
                                Adrr = "_rcvn[" + indice + "]";
                                new SendMessageTask().executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, Adrr);

                                triggerRcvn = false;
                            }

                            if (BufferInFlag) {
                                BufferInFlag = false;
                                String Temp;
                                if (BufferInW.contains("Falla")) {
                                    Temp = "Resp del Dispositivo: 3";
                                } else {
                                    Temp = BufferInW.substring(BufferInW.indexOf("Resp del Dispositivo: "));
                                }
                                if (Temp.contains(" 1")) {
                                    dispSta = 1;
                                }
                                if (Temp.contains(" 0")) {
                                    dispSta = 0;
                                }

                                if (Temp.contains(" 3")) {
                                    dispSta = 3;
                                }

                                triggerRcvn = true;

                                estadoDisp.add(String.valueOf(dispSta));
                                indice++;
                                BufferInW = "";
                            }

                            triggerRcvnWatch++;
                            if (triggerRcvnWatch > 20) {
                                triggerRcvn = false;
                                triggerRcvnWatch = 0;
                            }

                        } else {
                            estadoDisp.add(String.valueOf(dispSta));
                            indice++;
                        }

                        if (indice == names_D.size()) {
                            Step = 2;
                        }

                        //CmdSnd = false;
                        //BufferInW = "";

                    } else {
                        estadoDisp.add(String.valueOf(dispSta));
                        indice++;
                    }

                    if (indice == names_D.size()) {
                        Step = 2;

                    }

                    if (Step == 2) {
                        midPagerStrip.setBackgroundColor(getColor(R.color.colorConnected));
                        cmdActivo = "";
                        Step = 0;
                        ScanOk = true;


                    }

                }