//['EPCPSI' 'RPM' 'MPH' 'Gear' 'Temp']

double epc_predict(double * features) {
    double epcpwm;
    if (features[0] <= 46.5) {
        if (features[3] <= 1.5) {
            if (features[0] <= 33.5) {
                if (features[0] <= 28.5) {
                    if (features[0] <= 21.5) {
                        if (features[1] <= 2077.5) {
                            if (features[2] <= 7.5) {
                                epcpwm = 63.96666666666667;
                            } else {
                                epcpwm = 59.142857142857146;
                            }
                        } else {
                            epcpwm = 76.0;
                        }
                    } else {
                        if (features[4] <= 190.5) {
                            if (features[2] <= 33.0) {
                                if (features[0] <= 24.5) {
                                    epcpwm = 65.02;
                                } else {
                                    if (features[2] <= 10.5) {
                                        epcpwm = 67.93817204301075;
                                    } else {
                                        epcpwm = 65.54464285714286;
                                    }
                                }
                            } else {
                                if (features[4] <= 188.0) {
                                    epcpwm = 73.9090909090909;
                                } else {
                                    epcpwm = 61.0;
                                }
                            }
                        } else {
                            epcpwm = 69.5036496350365;
                        }
                    }
                } else {
                    if (features[4] <= 187.5) {
                        if (features[0] <= 31.5) {
                            if (features[2] <= 21.5) {
                                if (features[2] <= 19.5) {
                                    if (features[4] <= 184.5) {
                                        epcpwm = 67.59274193548387;
                                    } else {
                                        epcpwm = 69.53183520599251;
                                    }
                                } else {
                                    epcpwm = 61.416666666666664;
                                }
                            } else {
                                epcpwm = 75.84615384615384;
                            }
                        } else {
                            epcpwm = 70.47950819672131;
                        }
                    } else {
                        if (features[1] <= 1328.0) {
                            if (features[2] <= 67.5) {
                                if (features[0] <= 32.5) {
                                    epcpwm = 70.21963394342762;
                                } else {
                                    epcpwm = 71.71548117154812;
                                }
                            } else {
                                epcpwm = 63.81818181818182;
                            }
                        } else {
                            epcpwm = 73.10752688172043;
                        }
                    }
                }
            } else {
                if (features[0] <= 37.5) {
                    if (features[1] <= 793.0) {
                        if (features[4] <= 180.5) {
                            epcpwm = 68.33870967741936;
                        } else {
                            if (features[4] <= 187.5) {
                                epcpwm = 71.47315741583257;
                            } else {
                                epcpwm = 72.37323943661971;
                            }
                        }
                    } else {
                        if (features[4] <= 188.5) {
                            epcpwm = 72.77678571428571;
                        } else {
                            epcpwm = 73.91833333333334;
                        }
                    }
                } else {
                    if (features[4] <= 185.5) {
                        if (features[0] <= 42.5) {
                            if (features[1] <= 728.5) {
                                if (features[4] <= 180.5) {
                                    epcpwm = 70.54437869822485;
                                } else {
                                    epcpwm = 72.24606151537884;
                                }
                            } else {
                                epcpwm = 73.32778581765557;
                            }
                        } else {
                            if (features[1] <= 790.5) {
                                epcpwm = 73.92384105960265;
                            } else {
                                epcpwm = 75.33453237410072;
                            }
                        }
                    } else {
                        if (features[0] <= 43.5) {
                            if (features[4] <= 188.5) {
                                if (features[1] <= 967.5) {
                                    if (features[1] <= 631.5) {
                                        epcpwm = 73.83302583025831;
                                    } else {
                                        epcpwm = 73.07175660160735;
                                    }
                                } else {
                                    epcpwm = 74.26944226237235;
                                }
                            } else {
                                if (features[1] <= 700.5) {
                                    epcpwm = 74.06653683868873;
                                } else {
                                    epcpwm = 75.26340545625588;
                                }
                            }
                        } else {
                            if (features[1] <= 836.5) {
                                epcpwm = 75.02450032237266;
                            } else {
                                epcpwm = 76.74319727891157;
                            }
                        }
                    }
                }
            }
        } else {
            if (features[0] <= 38.5) {
                if (features[4] <= 190.5) {
                    if (features[1] <= 1009.5) {
                        if (features[3] <= 2.5) {
                            if (features[4] <= 185.5) {
                                if (features[4] <= 182.5) {
                                    if (features[1] <= 757.5) {
                                        if (features[1] <= 610.5) {
                                            epcpwm = 69.83783783783784;
                                        } else {
                                            if (features[2] <= 19.5) {
                                                epcpwm = 63.0919540229885;
                                            } else {
                                                epcpwm = 67.30555555555556;
                                            }
                                        }
                                    } else {
                                        if (features[0] <= 29.5) {
                                            epcpwm = 54.0;
                                        } else {
                                            if (features[1] <= 952.5) {
                                                if (features[2] <= 18.5) {
                                                    if (features[2] <= 7.0) {
                                                        epcpwm = 68.0;
                                                    } else {
                                                        epcpwm = 58.03846153846154;
                                                    }
                                                } else {
                                                    epcpwm = 63.70967741935484;
                                                }
                                            } else {
                                                if (features[0] <= 34.5) {
                                                    epcpwm = 70.1;
                                                } else {
                                                    epcpwm = 61.9375;
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[4] <= 184.5) {
                                        if (features[0] <= 29.5) {
                                            if (features[2] <= 15.5) {
                                                epcpwm = 58.5;
                                            } else {
                                                epcpwm = 66.52;
                                            }
                                        } else {
                                            if (features[1] <= 797.5) {
                                                if (features[2] <= 9.5) {
                                                    epcpwm = 68.9493670886076;
                                                } else {
                                                    if (features[1] <= 697.5) {
                                                        if (features[1] <= 681.0) {
                                                            if (features[2] <= 13.5) {
                                                                epcpwm = 67.68;
                                                            } else {
                                                                epcpwm = 60.72727272727273;
                                                            }
                                                        } else {
                                                            epcpwm = 55.8;
                                                        }
                                                    } else {
                                                        epcpwm = 66.9675925925926;
                                                    }
                                                }
                                            } else {
                                                if (features[2] <= 14.5) {
                                                    epcpwm = 63.09090909090909;
                                                } else {
                                                    epcpwm = 68.83495145631068;
                                                }
                                            }
                                        }
                                    } else {
                                        if (features[1] <= 659.0) {
                                            epcpwm = 70.24193548387096;
                                        } else {
                                            if (features[1] <= 812.5) {
                                                if (features[2] <= 11.5) {
                                                    epcpwm = 67.19672131147541;
                                                } else {
                                                    if (features[2] <= 17.5) {
                                                        if (features[1] <= 736.5) {
                                                            epcpwm = 66.53846153846153;
                                                        } else {
                                                            epcpwm = 60.24;
                                                        }
                                                    } else {
                                                        if (features[1] <= 754.5) {
                                                            epcpwm = 61.357142857142854;
                                                        } else {
                                                            epcpwm = 66.62857142857143;
                                                        }
                                                    }
                                                }
                                            } else {
                                                if (features[2] <= 17.5) {
                                                    if (features[1] <= 857.5) {
                                                        epcpwm = 68.66666666666667;
                                                    } else {
                                                        if (features[2] <= 10.5) {
                                                            epcpwm = 68.26923076923077;
                                                        } else {
                                                            epcpwm = 59.55555555555556;
                                                        }
                                                    }
                                                } else {
                                                    epcpwm = 67.75147928994083;
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (features[0] <= 32.5) {
                                    if (features[0] <= 28.5) {
                                        if (features[2] <= 27.0) {
                                            epcpwm = 65.54615384615384;
                                        } else {
                                            epcpwm = 55.714285714285715;
                                        }
                                    } else {
                                        epcpwm = 67.52056555269922;
                                    }
                                } else {
                                    if (features[2] <= 10.5) {
                                        if (features[0] <= 36.5) {
                                            epcpwm = 69.83153347732181;
                                        } else {
                                            if (features[2] <= 7.5) {
                                                epcpwm = 72.45;
                                            } else {
                                                epcpwm = 70.6911196911197;
                                            }
                                        }
                                    } else {
                                        if (features[1] <= 907.5) {
                                            if (features[1] <= 714.5) {
                                                epcpwm = 67.67630057803468;
                                            } else {
                                                if (features[0] <= 35.5) {
                                                    epcpwm = 68.73645680819912;
                                                } else {
                                                    epcpwm = 70.02060737527115;
                                                }
                                            }
                                        } else {
                                            if (features[2] <= 16.5) {
                                                if (features[2] <= 11.5) {
                                                    if (features[1] <= 974.5) {
                                                        epcpwm = 71.57142857142857;
                                                    } else {
                                                        epcpwm = 60.2;
                                                    }
                                                } else {
                                                    epcpwm = 60.61538461538461;
                                                }
                                            } else {
                                                if (features[4] <= 186.5) {
                                                    if (features[0] <= 34.5) {
                                                        epcpwm = 70.2;
                                                    } else {
                                                        epcpwm = 62.72222222222222;
                                                    }
                                                } else {
                                                    if (features[1] <= 910.0) {
                                                        epcpwm = 62.083333333333336;
                                                    } else {
                                                        epcpwm = 69.80952380952381;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[0] <= 34.5) {
                                if (features[1] <= 701.0) {
                                    epcpwm = 65.88888888888889;
                                } else {
                                    epcpwm = 58.16981132075472;
                                }
                            } else {
                                if (features[3] <= 3.5) {
                                    epcpwm = 61.029761904761905;
                                } else {
                                    epcpwm = 63.42045454545455;
                                }
                            }
                        }
                    } else {
                        if (features[2] <= 39.5) {
                            if (features[2] <= 14.5) {
                                if (features[4] <= 182.5) {
                                    if (features[1] <= 1501.5) {
                                        if (features[4] <= 180.5) {
                                            if (features[0] <= 29.5) {
                                                epcpwm = 53.4;
                                            } else {
                                                epcpwm = 58.424083769633505;
                                            }
                                        } else {
                                            if (features[1] <= 1152.5) {
                                                if (features[1] <= 1125.0) {
                                                    epcpwm = 60.75;
                                                } else {
                                                    if (features[0] <= 37.5) {
                                                        epcpwm = 69.16666666666667;
                                                    } else {
                                                        epcpwm = 60.714285714285715;
                                                    }
                                                }
                                            } else {
                                                if (features[0] <= 30.5) {
                                                    epcpwm = 55.08695652173913;
                                                } else {
                                                    if (features[0] <= 32.0) {
                                                        epcpwm = 75.0;
                                                    } else {
                                                        epcpwm = 58.98275862068966;
                                                    }
                                                }
                                            }
                                        }
                                    } else {
                                        if (features[4] <= 179.5) {
                                            epcpwm = 66.08108108108108;
                                        } else {
                                            epcpwm = 59.17391304347826;
                                        }
                                    }
                                } else {
                                    if (features[1] <= 1452.5) {
                                        if (features[4] <= 188.5) {
                                            if (features[3] <= 2.5) {
                                                if (features[0] <= 27.5) {
                                                    epcpwm = 63.23004694835681;
                                                } else {
                                                    if (features[1] <= 1101.5) {
                                                        if (features[2] <= 11.5) {
                                                            epcpwm = 66.86585365853658;
                                                        } else {
                                                            if (features[2] <= 13.5) {
                                                                epcpwm = 61.18181818181818;
                                                            } else {
                                                                epcpwm = 54.294117647058826;
                                                            }
                                                        }
                                                    } else {
                                                        if (features[1] <= 1126.5) {
                                                            epcpwm = 69.82407407407408;
                                                        } else {
                                                            if (features[1] <= 1321.5) {
                                                                epcpwm = 65.09141791044776;
                                                            } else {
                                                                if (features[2] <= 6.5) {
                                                                    if (features[2] <= 5.5) {
                                                                        epcpwm = 71.0;
                                                                    } else {
                                                                        epcpwm = 56.714285714285715;
                                                                    }
                                                                } else {
                                                                    if (features[4] <= 185.5) {
                                                                        if (features[1] <= 1391.5) {
                                                                            if (features[2] <= 13.5) {
                                                                                epcpwm = 58.523809523809526;
                                                                            } else {
                                                                                if (features[1] <= 1365.0) {
                                                                                    epcpwm = 61.63636363636363;
                                                                                } else {
                                                                                    epcpwm = 74.0;
                                                                                }
                                                                            }
                                                                        } else {
                                                                            if (features[2] <= 11.5) {
                                                                                epcpwm = 62.38095238095238;
                                                                            } else {
                                                                                if (features[4] <= 184.5) {
                                                                                    epcpwm = 67.33333333333333;
                                                                                } else {
                                                                                    epcpwm = 72.0;
                                                                                }
                                                                            }
                                                                        }
                                                                    } else {
                                                                        if (features[1] <= 1401.5) {
                                                                            epcpwm = 69.39097744360902;
                                                                        } else {
                                                                            epcpwm = 64.04444444444445;
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            } else {
                                                epcpwm = 59.964285714285715;
                                            }
                                        } else {
                                            if (features[0] <= 32.5) {
                                                epcpwm = 66.04744525547446;
                                            } else {
                                                if (features[1] <= 1222.5) {
                                                    if (features[2] <= 10.5) {
                                                        epcpwm = 70.94117647058823;
                                                    } else {
                                                        epcpwm = 68.20238095238095;
                                                    }
                                                } else {
                                                    if (features[1] <= 1407.0) {
                                                        epcpwm = 66.30357142857143;
                                                    } else {
                                                        epcpwm = 70.79411764705883;
                                                    }
                                                }
                                            }
                                        }
                                    } else {
                                        if (features[1] <= 2183.0) {
                                            if (features[0] <= 19.0) {
                                                if (features[1] <= 1967.5) {
                                                    epcpwm = 75.25;
                                                } else {
                                                    epcpwm = 51.0;
                                                }
                                            } else {
                                                if (features[0] <= 25.5) {
                                                    epcpwm = 58.333333333333336;
                                                } else {
                                                    if (features[4] <= 186.5) {
                                                        if (features[0] <= 32.5) {
                                                            if (features[1] <= 2063.0) {
                                                                epcpwm = 58.395348837209305;
                                                            } else {
                                                                epcpwm = 71.5;
                                                            }
                                                        } else {
                                                            if (features[1] <= 1496.5) {
                                                                if (features[1] <= 1487.0) {
                                                                    if (features[2] <= 13.5) {
                                                                        epcpwm = 61.473684210526315;
                                                                    } else {
                                                                        epcpwm = 68.75;
                                                                    }
                                                                } else {
                                                                    if (features[0] <= 36.5) {
                                                                        epcpwm = 77.66666666666667;
                                                                    } else {
                                                                        epcpwm = 67.4;
                                                                    }
                                                                }
                                                            } else {
                                                                if (features[1] <= 1757.0) {
                                                                    epcpwm = 60.46308724832215;
                                                                } else {
                                                                    if (features[0] <= 33.5) {
                                                                        epcpwm = 73.125;
                                                                    } else {
                                                                        if (features[2] <= 7.5) {
                                                                            epcpwm = 76.0;
                                                                        } else {
                                                                            epcpwm = 63.17391304347826;
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        if (features[2] <= 5.5) {
                                                            epcpwm = 71.0;
                                                        } else {
                                                            if (features[1] <= 1619.5) {
                                                                if (features[1] <= 1518.5) {
                                                                    if (features[2] <= 12.5) {
                                                                        if (features[1] <= 1504.0) {
                                                                            epcpwm = 66.28571428571429;
                                                                        } else {
                                                                            epcpwm = 59.0;
                                                                        }
                                                                    } else {
                                                                        if (features[4] <= 188.5) {
                                                                            epcpwm = 57.03448275862069;
                                                                        } else {
                                                                            if (features[0] <= 27.5) {
                                                                                epcpwm = 52.0;
                                                                            } else {
                                                                                epcpwm = 65.4;
                                                                            }
                                                                        }
                                                                    }
                                                                } else {
                                                                    if (features[0] <= 35.5) {
                                                                        if (features[0] <= 33.5) {
                                                                            if (features[2] <= 8.0) {
                                                                                epcpwm = 79.0;
                                                                            } else {
                                                                                epcpwm = 66.73770491803279;
                                                                            }
                                                                        } else {
                                                                            if (features[4] <= 189.5) {
                                                                                epcpwm = 56.93333333333333;
                                                                            } else {
                                                                                epcpwm = 74.2;
                                                                            }
                                                                        }
                                                                    } else {
                                                                        if (features[4] <= 187.5) {
                                                                            epcpwm = 66.0;
                                                                        } else {
                                                                            epcpwm = 75.11764705882354;
                                                                        }
                                                                    }
                                                                }
                                                            } else {
                                                                if (features[0] <= 37.5) {
                                                                    if (features[0] <= 27.5) {
                                                                        epcpwm = 67.54545454545455;
                                                                    } else {
                                                                        epcpwm = 60.61538461538461;
                                                                    }
                                                                } else {
                                                                    epcpwm = 67.37142857142857;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        } else {
                                            epcpwm = 55.714285714285715;
                                        }
                                    }
                                }
                            } else {
                                if (features[0] <= 34.5) {
                                    if (features[3] <= 2.5) {
                                        if (features[4] <= 186.5) {
                                            if (features[1] <= 1185.5) {
                                                epcpwm = 65.20253164556962;
                                            } else {
                                                if (features[4] <= 178.5) {
                                                    epcpwm = 56.40157480314961;
                                                } else {
                                                    if (features[1] <= 1429.5) {
                                                        if (features[1] <= 1394.0) {
                                                            if (features[0] <= 26.5) {
                                                                epcpwm = 62.43589743589744;
                                                            } else {
                                                                epcpwm = 58.285714285714285;
                                                            }
                                                        } else {
                                                            if (features[2] <= 18.5) {
                                                                if (features[1] <= 1412.0) {
                                                                    epcpwm = 72.38888888888889;
                                                                } else {
                                                                    epcpwm = 66.93103448275862;
                                                                }
                                                            } else {
                                                                if (features[2] <= 19.5) {
                                                                    epcpwm = 59.642857142857146;
                                                                } else {
                                                                    epcpwm = 68.5;
                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        if (features[1] <= 1505.5) {
                                                            epcpwm = 57.26775956284153;
                                                        } else {
                                                            if (features[4] <= 181.5) {
                                                                if (features[2] <= 26.5) {
                                                                    if (features[2] <= 23.0) {
                                                                        if (features[4] <= 180.5) {
                                                                            epcpwm = 65.27272727272727;
                                                                        } else {
                                                                            epcpwm = 56.61538461538461;
                                                                        }
                                                                    } else {
                                                                        if (features[0] <= 29.0) {
                                                                            epcpwm = 62.1578947368421;
                                                                        } else {
                                                                            epcpwm = 55.833333333333336;
                                                                        }
                                                                    }
                                                                } else {
                                                                    epcpwm = 70.45454545454545;
                                                                }
                                                            } else {
                                                                if (features[4] <= 184.5) {
                                                                    if (features[1] <= 1806.5) {
                                                                        epcpwm = 59.27450980392157;
                                                                    } else {
                                                                        epcpwm = 55.900826446280995;
                                                                    }
                                                                } else {
                                                                    if (features[2] <= 23.5) {
                                                                        if (features[1] <= 1682.0) {
                                                                            if (features[1] <= 1588.0) {
                                                                                epcpwm = 58.97115384615385;
                                                                            } else {
                                                                                if (features[1] <= 1625.0) {
                                                                                    epcpwm = 65.5;
                                                                                } else {
                                                                                    epcpwm = 61.09722222222222;
                                                                                }
                                                                            }
                                                                        } else {
                                                                            if (features[0] <= 24.5) {
                                                                                epcpwm = 52.75;
                                                                            } else {
                                                                                epcpwm = 59.135458167330675;
                                                                            }
                                                                        }
                                                                    } else {
                                                                        if (features[4] <= 185.5) {
                                                                            epcpwm = 58.035714285714285;
                                                                        } else {
                                                                            if (features[1] <= 2151.0) {
                                                                                epcpwm = 67.82926829268293;
                                                                            } else {
                                                                                epcpwm = 61.0;
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        } else {
                                            if (features[0] <= 29.5) {
                                                if (features[2] <= 20.5) {
                                                    if (features[1] <= 1492.5) {
                                                        if (features[1] <= 1199.0) {
                                                            if (features[2] <= 19.5) {
                                                                epcpwm = 55.4;
                                                            } else {
                                                                epcpwm = 68.5;
                                                            }
                                                        } else {
                                                            if (features[0] <= 28.5) {
                                                                epcpwm = 65.26890756302521;
                                                            } else {
                                                                epcpwm = 58.76923076923077;
                                                            }
                                                        }
                                                    } else {
                                                        if (features[0] <= 23.5) {
                                                            epcpwm = 52.333333333333336;
                                                        } else {
                                                            if (features[1] <= 1532.0) {
                                                                epcpwm = 57.875;
                                                            } else {
                                                                if (features[4] <= 187.5) {
                                                                    if (features[1] <= 1744.5) {
                                                                        epcpwm = 56.18421052631579;
                                                                    } else {
                                                                        epcpwm = 62.6875;
                                                                    }
                                                                } else {
                                                                    if (features[0] <= 27.5) {
                                                                        if (features[1] <= 1817.0) {
                                                                            if (features[0] <= 24.5) {
                                                                                if (features[1] <= 1652.0) {
                                                                                    epcpwm = 64.375;
                                                                                } else {
                                                                                    epcpwm = 53.714285714285715;
                                                                                }
                                                                            } else {
                                                                                epcpwm = 66.44155844155844;
                                                                            }
                                                                        } else {
                                                                            epcpwm = 55.0;
                                                                        }
                                                                    } else {
                                                                        epcpwm = 61.152542372881356;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                } else {
                                                    if (features[2] <= 22.5) {
                                                        if (features[0] <= 27.5) {
                                                            if (features[2] <= 21.5) {
                                                                epcpwm = 60.3125;
                                                            } else {
                                                                epcpwm = 53.0;
                                                            }
                                                        } else {
                                                            epcpwm = 59.50847457627118;
                                                        }
                                                    } else {
                                                        if (features[4] <= 187.5) {
                                                            epcpwm = 65.94871794871794;
                                                        } else {
                                                            if (features[1] <= 1443.5) {
                                                                epcpwm = 66.5;
                                                            } else {
                                                                if (features[1] <= 1905.5) {
                                                                    epcpwm = 56.48148148148148;
                                                                } else {
                                                                    epcpwm = 61.38297872340426;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            } else {
                                                if (features[1] <= 1957.0) {
                                                    if (features[2] <= 16.5) {
                                                        if (features[1] <= 1705.5) {
                                                            epcpwm = 58.674157303370784;
                                                        } else {
                                                            epcpwm = 68.0;
                                                        }
                                                    } else {
                                                        if (features[1] <= 1492.0) {
                                                            if (features[4] <= 188.5) {
                                                                if (features[2] <= 17.5) {
                                                                    if (features[4] <= 187.5) {
                                                                        epcpwm = 57.0;
                                                                    } else {
                                                                        epcpwm = 67.25;
                                                                    }
                                                                } else {
                                                                    epcpwm = 66.89795918367346;
                                                                }
                                                            } else {
                                                                if (features[2] <= 19.5) {
                                                                    epcpwm = 61.093333333333334;
                                                                } else {
                                                                    epcpwm = 67.22222222222223;
                                                                }
                                                            }
                                                        } else {
                                                            if (features[2] <= 22.5) {
                                                                if (features[1] <= 1793.0) {
                                                                    if (features[4] <= 187.5) {
                                                                        epcpwm = 59.258426966292134;
                                                                    } else {
                                                                        if (features[2] <= 18.5) {
                                                                            if (features[1] <= 1541.5) {
                                                                                epcpwm = 58.53846153846154;
                                                                            } else {
                                                                                if (features[1] <= 1590.0) {
                                                                                    epcpwm = 72.55555555555556;
                                                                                } else {
                                                                                    epcpwm = 66.07462686567165;
                                                                                }
                                                                            }
                                                                        } else {
                                                                            epcpwm = 62.07784431137725;
                                                                        }
                                                                    }
                                                                } else {
                                                                    if (features[2] <= 19.5) {
                                                                        epcpwm = 61.172413793103445;
                                                                    } else {
                                                                        if (features[2] <= 20.5) {
                                                                            if (features[1] <= 1861.0) {
                                                                                epcpwm = 74.55555555555556;
                                                                            } else {
                                                                                epcpwm = 60.0;
                                                                            }
                                                                        } else {
                                                                            if (features[0] <= 33.5) {
                                                                                if (features[1] <= 1825.0) {
                                                                                    epcpwm = 58.142857142857146;
                                                                                } else {
                                                                                    epcpwm = 68.48148148148148;
                                                                                }
                                                                            } else {
                                                                                epcpwm = 60.59090909090909;
                                                                            }
                                                                        }
                                                                    }
                                                                }
                                                            } else {
                                                                epcpwm = 59.23300970873787;
                                                            }
                                                        }
                                                    }
                                                } else {
                                                    if (features[1] <= 1986.5) {
                                                        epcpwm = 71.63636363636364;
                                                    } else {
                                                        if (features[0] <= 30.5) {
                                                            if (features[2] <= 19.5) {
                                                                epcpwm = 56.0;
                                                            } else {
                                                                epcpwm = 70.23076923076923;
                                                            }
                                                        } else {
                                                            if (features[2] <= 27.0) {
                                                                epcpwm = 64.1;
                                                            } else {
                                                                epcpwm = 70.52173913043478;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    } else {
                                        if (features[2] <= 26.5) {
                                            if (features[0] <= 30.5) {
                                                if (features[0] <= 8.0) {
                                                    epcpwm = 67.55555555555556;
                                                } else {
                                                    if (features[1] <= 1967.0) {
                                                        if (features[0] <= 28.5) {
                                                            epcpwm = 56.11734693877551;
                                                        } else {
                                                            epcpwm = 57.63509749303621;
                                                        }
                                                    } else {
                                                        if (features[2] <= 20.5) {
                                                            epcpwm = 76.0;
                                                        } else {
                                                            epcpwm = 60.333333333333336;
                                                        }
                                                    }
                                                }
                                            } else {
                                                if (features[4] <= 186.5) {
                                                    epcpwm = 58.333333333333336;
                                                } else {
                                                    epcpwm = 59.62838915470494;
                                                }
                                            }
                                        } else {
                                            if (features[0] <= 30.5) {
                                                if (features[1] <= 2399.5) {
                                                    if (features[0] <= 3.0) {
                                                        epcpwm = 71.0;
                                                    } else {
                                                        epcpwm = 59.009404388714735;
                                                    }
                                                } else {
                                                    if (features[0] <= 25.5) {
                                                        epcpwm = 74.5;
                                                    } else {
                                                        if (features[0] <= 27.5) {
                                                            epcpwm = 50.0;
                                                        } else {
                                                            epcpwm = 62.75;
                                                        }
                                                    }
                                                }
                                            } else {
                                                if (features[4] <= 181.5) {
                                                    epcpwm = 58.6319018404908;
                                                } else {
                                                    if (features[2] <= 35.5) {
                                                        epcpwm = 60.55710306406685;
                                                    } else {
                                                        epcpwm = 61.92439024390244;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[4] <= 185.5) {
                                        if (features[4] <= 182.5) {
                                            if (features[2] <= 35.5) {
                                                if (features[2] <= 21.5) {
                                                    epcpwm = 58.748387096774195;
                                                } else {
                                                    epcpwm = 60.09722222222222;
                                                }
                                            } else {
                                                epcpwm = 62.5;
                                            }
                                        } else {
                                            if (features[0] <= 36.5) {
                                                if (features[2] <= 29.5) {
                                                    epcpwm = 60.19041278295606;
                                                } else {
                                                    epcpwm = 62.1;
                                                }
                                            } else {
                                                if (features[2] <= 18.5) {
                                                    if (features[1] <= 1442.5) {
                                                        if (features[1] <= 1396.0) {
                                                            if (features[2] <= 16.5) {
                                                                epcpwm = 67.94736842105263;
                                                            } else {
                                                                epcpwm = 62.72549019607843;
                                                            }
                                                        } else {
                                                            if (features[4] <= 183.5) {
                                                                epcpwm = 76.35714285714286;
                                                            } else {
                                                                if (features[2] <= 17.5) {
                                                                    epcpwm = 57.4;
                                                                } else {
                                                                    epcpwm = 68.75;
                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        epcpwm = 61.20652173913044;
                                                    }
                                                } else {
                                                    epcpwm = 61.30111902339776;
                                                }
                                            }
                                        }
                                    } else {
                                        if (features[1] <= 2298.5) {
                                            if (features[1] <= 1839.5) {
                                                if (features[3] <= 3.5) {
                                                    if (features[2] <= 19.5) {
                                                        if (features[4] <= 187.5) {
                                                            epcpwm = 61.7007299270073;
                                                        } else {
                                                            if (features[1] <= 1525.0) {
                                                                if (features[1] <= 1483.5) {
                                                                    if (features[1] <= 1434.5) {
                                                                        if (features[1] <= 1128.0) {
                                                                            if (features[1] <= 1107.0) {
                                                                                epcpwm = 64.28125;
                                                                            } else {
                                                                                epcpwm = 75.6;
                                                                            }
                                                                        } else {
                                                                            if (features[1] <= 1243.0) {
                                                                                epcpwm = 60.50526315789474;
                                                                            } else {
                                                                                epcpwm = 63.4625;
                                                                            }
                                                                        }
                                                                    } else {
                                                                        if (features[2] <= 16.5) {
                                                                            epcpwm = 59.9;
                                                                        } else {
                                                                            if (features[4] <= 189.5) {
                                                                                epcpwm = 64.19047619047619;
                                                                            } else {
                                                                                epcpwm = 71.26315789473684;
                                                                            }
                                                                        }
                                                                    }
                                                                } else {
                                                                    epcpwm = 59.964285714285715;
                                                                }
                                                            } else {
                                                                if (features[1] <= 1547.0) {
                                                                    epcpwm = 70.15789473684211;
                                                                } else {
                                                                    if (features[4] <= 188.5) {
                                                                        if (features[1] <= 1608.0) {
                                                                            epcpwm = 62.82608695652174;
                                                                        } else {
                                                                            if (features[1] <= 1657.0) {
                                                                                epcpwm = 71.55555555555556;
                                                                            } else {
                                                                                epcpwm = 65.975;
                                                                            }
                                                                        }
                                                                    } else {
                                                                        epcpwm = 63.16981132075472;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        if (features[2] <= 23.5) {
                                                            epcpwm = 61.02290076335878;
                                                        } else {
                                                            if (features[3] <= 2.5) {
                                                                if (features[1] <= 1497.0) {
                                                                    epcpwm = 71.21875;
                                                                } else {
                                                                    epcpwm = 63.294117647058826;
                                                                }
                                                            } else {
                                                                epcpwm = 61.82613510520487;
                                                            }
                                                        }
                                                    }
                                                } else {
                                                    epcpwm = 63.66437177280551;
                                                }
                                            } else {
                                                if (features[3] <= 2.5) {
                                                    if (features[1] <= 1842.0) {
                                                        epcpwm = 76.42857142857143;
                                                    } else {
                                                        if (features[2] <= 24.5) {
                                                            if (features[1] <= 1869.5) {
                                                                if (features[1] <= 1864.5) {
                                                                    if (features[2] <= 20.5) {
                                                                        epcpwm = 61.18181818181818;
                                                                    } else {
                                                                        if (features[1] <= 1856.5) {
                                                                            epcpwm = 63.1578947368421;
                                                                        } else {
                                                                            if (features[2] <= 21.5) {
                                                                                epcpwm = 75.33333333333333;
                                                                            } else {
                                                                                epcpwm = 64.71428571428571;
                                                                            }
                                                                        }
                                                                    }
                                                                } else {
                                                                    epcpwm = 70.45;
                                                                }
                                                            } else {
                                                                epcpwm = 63.40946502057613;
                                                            }
                                                        } else {
                                                            if (features[0] <= 35.5) {
                                                                epcpwm = 71.5;
                                                            } else {
                                                                epcpwm = 65.85714285714286;
                                                            }
                                                        }
                                                    }
                                                } else {
                                                    if (features[1] <= 2056.5) {
                                                        epcpwm = 63.23508771929824;
                                                    } else {
                                                        epcpwm = 61.795539033457246;
                                                    }
                                                }
                                            }
                                        } else {
                                            if (features[3] <= 2.5) {
                                                if (features[2] <= 19.0) {
                                                    epcpwm = 51.0;
                                                } else {
                                                    if (features[4] <= 189.5) {
                                                        epcpwm = 72.73584905660377;
                                                    } else {
                                                        epcpwm = 61.142857142857146;
                                                    }
                                                }
                                            } else {
                                                epcpwm = 63.30434782608695;
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[0] <= 34.5) {
                                if (features[0] <= 30.5) {
                                    epcpwm = 61.31404958677686;
                                } else {
                                    if (features[4] <= 184.5) {
                                        epcpwm = 60.90151515151515;
                                    } else {
                                        if (features[3] <= 3.5) {
                                            epcpwm = 60.666666666666664;
                                        } else {
                                            if (features[1] <= 2625.0) {
                                                epcpwm = 63.51048951048951;
                                            } else {
                                                epcpwm = 71.77777777777777;
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (features[4] <= 184.5) {
                                    epcpwm = 63.067092651757186;
                                } else {
                                    if (features[1] <= 2645.5) {
                                        epcpwm = 64.88008213552361;
                                    } else {
                                        epcpwm = 60.833333333333336;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[0] <= 31.5) {
                        if (features[1] <= 2168.5) {
                            if (features[1] <= 1037.5) {
                                if (features[3] <= 2.5) {
                                    epcpwm = 68.59166666666667;
                                } else {
                                    epcpwm = 55.714285714285715;
                                }
                            } else {
                                if (features[1] <= 1770.0) {
                                    if (features[4] <= 192.5) {
                                        if (features[2] <= 12.5) {
                                            if (features[4] <= 191.5) {
                                                if (features[1] <= 1532.5) {
                                                    if (features[2] <= 7.5) {
                                                        epcpwm = 60.0;
                                                    } else {
                                                        epcpwm = 68.10810810810811;
                                                    }
                                                } else {
                                                    epcpwm = 57.857142857142854;
                                                }
                                            } else {
                                                if (features[2] <= 9.5) {
                                                    epcpwm = 64.5;
                                                } else {
                                                    epcpwm = 55.57142857142857;
                                                }
                                            }
                                        } else {
                                            if (features[2] <= 22.5) {
                                                if (features[0] <= 24.5) {
                                                    epcpwm = 52.72727272727273;
                                                } else {
                                                    epcpwm = 58.87586206896552;
                                                }
                                            } else {
                                                if (features[3] <= 2.5) {
                                                    epcpwm = 70.1;
                                                } else {
                                                    if (features[2] <= 29.5) {
                                                        epcpwm = 58.94444444444444;
                                                    } else {
                                                        epcpwm = 62.1978021978022;
                                                    }
                                                }
                                            }
                                        }
                                    } else {
                                        if (features[3] <= 2.5) {
                                            if (features[4] <= 194.5) {
                                                epcpwm = 68.65789473684211;
                                            } else {
                                                epcpwm = 57.0;
                                            }
                                        } else {
                                            if (features[3] <= 3.5) {
                                                epcpwm = 59.60952380952381;
                                            } else {
                                                if (features[0] <= 24.5) {
                                                    epcpwm = 71.5;
                                                } else {
                                                    epcpwm = 62.935064935064936;
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[0] <= 30.5) {
                                        if (features[3] <= 2.5) {
                                            if (features[2] <= 20.5) {
                                                if (features[4] <= 192.5) {
                                                    epcpwm = 60.96;
                                                } else {
                                                    epcpwm = 68.47619047619048;
                                                }
                                            } else {
                                                epcpwm = 69.56060606060606;
                                            }
                                        } else {
                                            if (features[3] <= 3.5) {
                                                epcpwm = 61.08108108108108;
                                            } else {
                                                if (features[0] <= 28.5) {
                                                    if (features[0] <= 23.5) {
                                                        epcpwm = 73.0;
                                                    } else {
                                                        epcpwm = 63.14556962025316;
                                                    }
                                                } else {
                                                    epcpwm = 64.65948275862068;
                                                }
                                            }
                                        }
                                    } else {
                                        epcpwm = 65.87904066736183;
                                    }
                                }
                            }
                        } else {
                            if (features[0] <= 26.5) {
                                if (features[2] <= 41.5) {
                                    epcpwm = 68.4;
                                } else {
                                    epcpwm = 55.17283950617284;
                                }
                            } else {
                                if (features[0] <= 28.5) {
                                    if (features[2] <= 56.5) {
                                        epcpwm = 60.43617021276596;
                                    } else {
                                        epcpwm = 55.75757575757576;
                                    }
                                } else {
                                    epcpwm = 61.401496259351624;
                                }
                            }
                        }
                    } else {
                        if (features[3] <= 2.5) {
                            if (features[1] <= 1052.0) {
                                if (features[0] <= 35.5) {
                                    epcpwm = 70.45471698113208;
                                } else {
                                    if (features[1] <= 889.0) {
                                        epcpwm = 73.0592105263158;
                                    } else {
                                        epcpwm = 71.21764705882353;
                                    }
                                }
                            } else {
                                if (features[2] <= 20.5) {
                                    if (features[4] <= 192.5) {
                                        if (features[2] <= 12.5) {
                                            if (features[1] <= 1557.5) {
                                                if (features[1] <= 1150.5) {
                                                    if (features[1] <= 1073.5) {
                                                        epcpwm = 71.14285714285714;
                                                    } else {
                                                        epcpwm = 62.82608695652174;
                                                    }
                                                } else {
                                                    if (features[1] <= 1390.0) {
                                                        epcpwm = 71.58333333333333;
                                                    } else {
                                                        if (features[1] <= 1454.5) {
                                                            epcpwm = 63.06666666666667;
                                                        } else {
                                                            if (features[2] <= 10.5) {
                                                                epcpwm = 65.55555555555556;
                                                            } else {
                                                                epcpwm = 74.66666666666667;
                                                            }
                                                        }
                                                    }
                                                }
                                            } else {
                                                epcpwm = 59.6;
                                            }
                                        } else {
                                            epcpwm = 61.54617414248021;
                                        }
                                    } else {
                                        if (features[4] <= 194.5) {
                                            if (features[0] <= 36.5) {
                                                if (features[4] <= 193.5) {
                                                    if (features[2] <= 12.5) {
                                                        epcpwm = 70.9245283018868;
                                                    } else {
                                                        if (features[1] <= 1356.5) {
                                                            if (features[0] <= 34.5) {
                                                                epcpwm = 66.75;
                                                            } else {
                                                                epcpwm = 60.17391304347826;
                                                            }
                                                        } else {
                                                            if (features[1] <= 1590.5) {
                                                                epcpwm = 70.5;
                                                            } else {
                                                                epcpwm = 66.02173913043478;
                                                            }
                                                        }
                                                    }
                                                } else {
                                                    if (features[2] <= 11.5) {
                                                        epcpwm = 64.07692307692308;
                                                    } else {
                                                        epcpwm = 71.28813559322033;
                                                    }
                                                }
                                            } else {
                                                if (features[2] <= 14.5) {
                                                    epcpwm = 69.71084337349397;
                                                } else {
                                                    epcpwm = 73.54166666666667;
                                                }
                                            }
                                        } else {
                                            epcpwm = 64.6;
                                        }
                                    }
                                } else {
                                    if (features[1] <= 1991.5) {
                                        if (features[1] <= 1267.0) {
                                            if (features[2] <= 21.5) {
                                                epcpwm = 54.0;
                                            } else {
                                                epcpwm = 71.6;
                                            }
                                        } else {
                                            epcpwm = 73.52511415525115;
                                        }
                                    } else {
                                        if (features[2] <= 24.0) {
                                            epcpwm = 63.77272727272727;
                                        } else {
                                            if (features[4] <= 192.0) {
                                                epcpwm = 56.0;
                                            } else {
                                                epcpwm = 73.16666666666667;
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[2] <= 38.5) {
                                if (features[2] <= 27.5) {
                                    if (features[0] <= 34.5) {
                                        epcpwm = 61.00409836065574;
                                    } else {
                                        if (features[4] <= 191.5) {
                                            epcpwm = 61.41818181818182;
                                        } else {
                                            epcpwm = 63.1500904159132;
                                        }
                                    }
                                } else {
                                    if (features[0] <= 34.5) {
                                        if (features[1] <= 2227.0) {
                                            epcpwm = 62.884393063583815;
                                        } else {
                                            epcpwm = 53.0;
                                        }
                                    } else {
                                        epcpwm = 64.52253909843606;
                                    }
                                }
                            } else {
                                if (features[1] <= 2169.5) {
                                    if (features[0] <= 34.5) {
                                        if (features[1] <= 1997.5) {
                                            epcpwm = 65.54970760233918;
                                        } else {
                                            if (features[1] <= 2035.5) {
                                                epcpwm = 68.11496062992126;
                                            } else {
                                                epcpwm = 66.48443665059185;
                                            }
                                        }
                                    } else {
                                        if (features[2] <= 47.5) {
                                            epcpwm = 66.32208588957056;
                                        } else {
                                            if (features[1] <= 2044.5) {
                                                if (features[1] <= 2005.5) {
                                                    if (features[2] <= 51.5) {
                                                        epcpwm = 68.15859872611465;
                                                    } else {
                                                        epcpwm = 66.60162601626017;
                                                    }
                                                } else {
                                                    epcpwm = 69.85616438356165;
                                                }
                                            } else {
                                                if (features[2] <= 53.5) {
                                                    epcpwm = 67.15026833631485;
                                                } else {
                                                    if (features[4] <= 191.5) {
                                                        epcpwm = 66.38922155688623;
                                                    } else {
                                                        epcpwm = 68.24363749224085;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[0] <= 36.5) {
                                        if (features[2] <= 45.5) {
                                            epcpwm = 66.19298245614036;
                                        } else {
                                            if (features[0] <= 34.5) {
                                                if (features[4] <= 193.5) {
                                                    if (features[2] <= 49.5) {
                                                        epcpwm = 59.28125;
                                                    } else {
                                                        epcpwm = 63.02949852507375;
                                                    }
                                                } else {
                                                    epcpwm = 64.11389961389962;
                                                }
                                            } else {
                                                if (features[1] <= 2396.0) {
                                                    epcpwm = 64.34059945504087;
                                                } else {
                                                    epcpwm = 66.59740259740259;
                                                }
                                            }
                                        }
                                    } else {
                                        if (features[1] <= 2399.5) {
                                            epcpwm = 65.96160794941282;
                                        } else {
                                            if (features[1] <= 2785.0) {
                                                epcpwm = 67.72681704260651;
                                            } else {
                                                epcpwm = 60.111111111111114;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[4] <= 190.5) {
                    if (features[4] <= 185.5) {
                        if (features[3] <= 2.5) {
                            if (features[4] <= 182.5) {
                                if (features[2] <= 21.5) {
                                    if (features[1] <= 626.0) {
                                        if (features[2] <= 11.5) {
                                            if (features[0] <= 40.5) {
                                                epcpwm = 71.7;
                                            } else {
                                                epcpwm = 62.892857142857146;
                                            }
                                        } else {
                                            if (features[4] <= 181.0) {
                                                epcpwm = 71.8529411764706;
                                            } else {
                                                epcpwm = 64.25;
                                            }
                                        }
                                    } else {
                                        if (features[2] <= 18.5) {
                                            if (features[1] <= 1857.5) {
                                                if (features[0] <= 43.5) {
                                                    if (features[2] <= 10.5) {
                                                        if (features[4] <= 180.5) {
                                                            if (features[1] <= 1289.5) {
                                                                epcpwm = 61.7196261682243;
                                                            } else {
                                                                if (features[1] <= 1318.0) {
                                                                    epcpwm = 72.45454545454545;
                                                                } else {
                                                                    epcpwm = 61.8125;
                                                                }
                                                            }
                                                        } else {
                                                            if (features[1] <= 900.0) {
                                                                epcpwm = 61.15384615384615;
                                                            } else {
                                                                if (features[1] <= 1153.5) {
                                                                    epcpwm = 69.47619047619048;
                                                                } else {
                                                                    epcpwm = 61.8;
                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        epcpwm = 61.27149321266968;
                                                    }
                                                } else {
                                                    epcpwm = 63.698412698412696;
                                                }
                                            } else {
                                                if (features[0] <= 41.5) {
                                                    epcpwm = 71.47826086956522;
                                                } else {
                                                    epcpwm = 64.42857142857143;
                                                }
                                            }
                                        } else {
                                            if (features[1] <= 962.5) {
                                                if (features[1] <= 813.0) {
                                                    if (features[4] <= 181.5) {
                                                        epcpwm = 69.42105263157895;
                                                    } else {
                                                        epcpwm = 63.17142857142857;
                                                    }
                                                } else {
                                                    epcpwm = 71.16666666666667;
                                                }
                                            } else {
                                                if (features[4] <= 178.5) {
                                                    epcpwm = 61.80232558139535;
                                                } else {
                                                    if (features[4] <= 179.5) {
                                                        if (features[1] <= 1522.5) {
                                                            epcpwm = 62.1;
                                                        } else {
                                                            epcpwm = 72.8;
                                                        }
                                                    } else {
                                                        epcpwm = 62.13513513513514;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[1] <= 2088.5) {
                                        if (features[4] <= 177.5) {
                                            epcpwm = 71.01652892561984;
                                        } else {
                                            if (features[1] <= 1492.0) {
                                                epcpwm = 70.97777777777777;
                                            } else {
                                                if (features[0] <= 41.5) {
                                                    if (features[2] <= 23.5) {
                                                        epcpwm = 69.66304347826087;
                                                    } else {
                                                        epcpwm = 61.09090909090909;
                                                    }
                                                } else {
                                                    epcpwm = 63.457142857142856;
                                                }
                                            }
                                        }
                                    } else {
                                        epcpwm = 63.86363636363637;
                                    }
                                }
                            } else {
                                if (features[1] <= 927.5) {
                                    if (features[1] <= 804.5) {
                                        if (features[1] <= 654.0) {
                                            if (features[0] <= 45.5) {
                                                if (features[2] <= 13.5) {
                                                    epcpwm = 71.05555555555556;
                                                } else {
                                                    epcpwm = 68.62962962962963;
                                                }
                                            } else {
                                                epcpwm = 64.45833333333333;
                                            }
                                        } else {
                                            if (features[4] <= 184.5) {
                                                if (features[1] <= 744.5) {
                                                    if (features[0] <= 41.5) {
                                                        epcpwm = 68.6;
                                                    } else {
                                                        if (features[2] <= 18.5) {
                                                            if (features[2] <= 9.5) {
                                                                epcpwm = 67.86111111111111;
                                                            } else {
                                                                epcpwm = 62.73684210526316;
                                                            }
                                                        } else {
                                                            epcpwm = 68.55263157894737;
                                                        }
                                                    }
                                                } else {
                                                    epcpwm = 68.04146341463415;
                                                }
                                            } else {
                                                if (features[1] <= 723.5) {
                                                    if (features[2] <= 17.5) {
                                                        epcpwm = 67.25409836065573;
                                                    } else {
                                                        epcpwm = 62.388888888888886;
                                                    }
                                                } else {
                                                    epcpwm = 64.54143646408839;
                                                }
                                            }
                                        }
                                    } else {
                                        if (features[2] <= 12.5) {
                                            epcpwm = 64.5774647887324;
                                        } else {
                                            if (features[2] <= 25.5) {
                                                if (features[1] <= 898.5) {
                                                    if (features[1] <= 870.5) {
                                                        epcpwm = 69.4896265560166;
                                                    } else {
                                                        if (features[0] <= 44.5) {
                                                            epcpwm = 67.79591836734694;
                                                        } else {
                                                            epcpwm = 62.91304347826087;
                                                        }
                                                    }
                                                } else {
                                                    if (features[2] <= 20.5) {
                                                        epcpwm = 72.46753246753246;
                                                    } else {
                                                        epcpwm = 67.33333333333333;
                                                    }
                                                }
                                            } else {
                                                epcpwm = 61.92307692307692;
                                            }
                                        }
                                    }
                                } else {
                                    if (features[1] <= 1539.5) {
                                        if (features[1] <= 1368.5) {
                                            if (features[2] <= 20.5) {
                                                if (features[2] <= 11.5) {
                                                    if (features[1] <= 1086.5) {
                                                        epcpwm = 62.294117647058826;
                                                    } else {
                                                        if (features[1] <= 1149.0) {
                                                            if (features[1] <= 1113.5) {
                                                                if (features[4] <= 184.5) {
                                                                    epcpwm = 64.16666666666667;
                                                                } else {
                                                                    epcpwm = 74.88888888888889;
                                                                }
                                                            } else {
                                                                epcpwm = 72.93055555555556;
                                                            }
                                                        } else {
                                                            if (features[2] <= 10.5) {
                                                                epcpwm = 64.35714285714286;
                                                            } else {
                                                                epcpwm = 70.47619047619048;
                                                            }
                                                        }
                                                    }
                                                } else {
                                                    epcpwm = 63.93681318681319;
                                                }
                                            } else {
                                                if (features[2] <= 27.5) {
                                                    epcpwm = 70.53658536585365;
                                                } else {
                                                    epcpwm = 63.72727272727273;
                                                }
                                            }
                                        } else {
                                            if (features[2] <= 15.5) {
                                                if (features[1] <= 1452.0) {
                                                    if (features[2] <= 10.5) {
                                                        if (features[1] <= 1380.5) {
                                                            epcpwm = 75.0;
                                                        } else {
                                                            epcpwm = 63.45454545454545;
                                                        }
                                                    } else {
                                                        if (features[2] <= 13.5) {
                                                            epcpwm = 72.67647058823529;
                                                        } else {
                                                            if (features[1] <= 1407.5) {
                                                                if (features[0] <= 43.5) {
                                                                    epcpwm = 68.93939393939394;
                                                                } else {
                                                                    epcpwm = 63.125;
                                                                }
                                                            } else {
                                                                if (features[0] <= 40.5) {
                                                                    epcpwm = 68.07692307692308;
                                                                } else {
                                                                    epcpwm = 76.3157894736842;
                                                                }
                                                            }
                                                        }
                                                    }
                                                } else {
                                                    if (features[1] <= 1515.5) {
                                                        if (features[2] <= 10.5) {
                                                            epcpwm = 68.77777777777777;
                                                        } else {
                                                            epcpwm = 64.62790697674419;
                                                        }
                                                    } else {
                                                        epcpwm = 71.43478260869566;
                                                    }
                                                }
                                            } else {
                                                if (features[0] <= 45.5) {
                                                    if (features[1] <= 1535.0) {
                                                        if (features[1] <= 1428.5) {
                                                            if (features[4] <= 184.5) {
                                                                if (features[1] <= 1392.5) {
                                                                    epcpwm = 60.285714285714285;
                                                                } else {
                                                                    epcpwm = 71.89655172413794;
                                                                }
                                                            } else {
                                                                epcpwm = 63.450980392156865;
                                                            }
                                                        } else {
                                                            epcpwm = 63.17788461538461;
                                                        }
                                                    } else {
                                                        epcpwm = 72.0;
                                                    }
                                                } else {
                                                    epcpwm = 71.03125;
                                                }
                                            }
                                        }
                                    } else {
                                        if (features[4] <= 183.5) {
                                            if (features[2] <= 17.5) {
                                                if (features[1] <= 1732.0) {
                                                    epcpwm = 62.08860759493671;
                                                } else {
                                                    if (features[2] <= 13.5) {
                                                        epcpwm = 76.0;
                                                    } else {
                                                        epcpwm = 61.25;
                                                    }
                                                }
                                            } else {
                                                if (features[1] <= 1723.0) {
                                                    if (features[0] <= 43.5) {
                                                        if (features[1] <= 1652.5) {
                                                            epcpwm = 68.1875;
                                                        } else {
                                                            epcpwm = 72.40350877192982;
                                                        }
                                                    } else {
                                                        epcpwm = 64.0;
                                                    }
                                                } else {
                                                    epcpwm = 63.074074074074076;
                                                }
                                            }
                                        } else {
                                            if (features[0] <= 42.5) {
                                                if (features[1] <= 1681.5) {
                                                    if (features[4] <= 184.5) {
                                                        if (features[2] <= 17.5) {
                                                            epcpwm = 62.67307692307692;
                                                        } else {
                                                            if (features[2] <= 19.5) {
                                                                epcpwm = 72.1304347826087;
                                                            } else {
                                                                epcpwm = 60.2;
                                                            }
                                                        }
                                                    } else {
                                                        epcpwm = 62.53968253968254;
                                                    }
                                                } else {
                                                    epcpwm = 62.618729096989966;
                                                }
                                            } else {
                                                epcpwm = 64.73422562141491;
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[2] <= 44.5) {
                                if (features[0] <= 42.5) {
                                    epcpwm = 62.380208333333336;
                                } else {
                                    if (features[1] <= 1582.5) {
                                        epcpwm = 63.917382683410445;
                                    } else {
                                        epcpwm = 65.06122448979592;
                                    }
                                }
                            } else {
                                if (features[0] <= 42.5) {
                                    epcpwm = 65.77196652719665;
                                } else {
                                    epcpwm = 67.7683923705722;
                                }
                            }
                        }
                    } else {
                        if (features[2] <= 11.5) {
                            if (features[1] <= 1425.0) {
                                if (features[4] <= 188.5) {
                                    if (features[0] <= 42.5) {
                                        if (features[1] <= 955.5) {
                                            if (features[3] <= 2.5) {
                                                epcpwm = 70.5591054313099;
                                            } else {
                                                epcpwm = 63.25;
                                            }
                                        } else {
                                            if (features[1] <= 1325.5) {
                                                epcpwm = 66.80838323353294;
                                            } else {
                                                if (features[1] <= 1407.0) {
                                                    epcpwm = 72.62745098039215;
                                                } else {
                                                    epcpwm = 65.6;
                                                }
                                            }
                                        }
                                    } else {
                                        if (features[4] <= 187.5) {
                                            if (features[4] <= 186.5) {
                                                if (features[1] <= 1330.0) {
                                                    epcpwm = 67.0;
                                                } else {
                                                    if (features[1] <= 1347.5) {
                                                        epcpwm = 78.25;
                                                    } else {
                                                        epcpwm = 66.53333333333333;
                                                    }
                                                }
                                            } else {
                                                if (features[1] <= 586.0) {
                                                    epcpwm = 61.5;
                                                } else {
                                                    epcpwm = 70.7381974248927;
                                                }
                                            }
                                        } else {
                                            if (features[1] <= 689.0) {
                                                epcpwm = 63.30909090909091;
                                            } else {
                                                if (features[1] <= 1089.5) {
                                                    epcpwm = 71.31914893617021;
                                                } else {
                                                    if (features[2] <= 7.5) {
                                                        if (features[1] <= 1162.5) {
                                                            epcpwm = 62.0;
                                                        } else {
                                                            epcpwm = 78.0;
                                                        }
                                                    } else {
                                                        epcpwm = 62.6;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[1] <= 701.5) {
                                        if (features[2] <= 7.5) {
                                            if (features[1] <= 647.0) {
                                                if (features[4] <= 189.5) {
                                                    epcpwm = 71.26388888888889;
                                                } else {
                                                    epcpwm = 65.21428571428571;
                                                }
                                            } else {
                                                epcpwm = 73.25;
                                            }
                                        } else {
                                            if (features[3] <= 2.5) {
                                                if (features[1] <= 649.5) {
                                                    if (features[4] <= 189.5) {
                                                        epcpwm = 61.7037037037037;
                                                    } else {
                                                        epcpwm = 69.63636363636364;
                                                    }
                                                } else {
                                                    if (features[0] <= 43.5) {
                                                        epcpwm = 70.07865168539325;
                                                    } else {
                                                        if (features[1] <= 694.5) {
                                                            epcpwm = 65.05263157894737;
                                                        } else {
                                                            epcpwm = 76.66666666666667;
                                                        }
                                                    }
                                                }
                                            } else {
                                                epcpwm = 64.5;
                                            }
                                        }
                                    } else {
                                        if (features[1] <= 1182.5) {
                                            if (features[2] <= 9.5) {
                                                if (features[0] <= 43.5) {
                                                    epcpwm = 73.02433090024331;
                                                } else {
                                                    epcpwm = 74.73737373737374;
                                                }
                                            } else {
                                                epcpwm = 72.1070496083551;
                                            }
                                        } else {
                                            if (features[4] <= 189.5) {
                                                epcpwm = 72.35643564356435;
                                            } else {
                                                if (features[1] <= 1282.5) {
                                                    if (features[0] <= 40.5) {
                                                        epcpwm = 72.75;
                                                    } else {
                                                        epcpwm = 64.23076923076923;
                                                    }
                                                } else {
                                                    epcpwm = 71.05128205128206;
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (features[1] <= 1427.5) {
                                    epcpwm = 56.0;
                                } else {
                                    epcpwm = 66.38591549295775;
                                }
                            }
                        } else {
                            if (features[0] <= 42.5) {
                                if (features[1] <= 844.5) {
                                    if (features[3] <= 2.5) {
                                        if (features[1] <= 725.5) {
                                            if (features[4] <= 188.5) {
                                                epcpwm = 68.365625;
                                            } else {
                                                if (features[2] <= 12.5) {
                                                    if (features[1] <= 688.0) {
                                                        epcpwm = 65.90243902439025;
                                                    } else {
                                                        epcpwm = 72.24324324324324;
                                                    }
                                                } else {
                                                    if (features[1] <= 652.5) {
                                                        epcpwm = 69.19565217391305;
                                                    } else {
                                                        if (features[4] <= 189.5) {
                                                            if (features[1] <= 715.5) {
                                                                epcpwm = 61.73529411764706;
                                                            } else {
                                                                epcpwm = 69.33333333333333;
                                                            }
                                                        } else {
                                                            epcpwm = 66.29230769230769;
                                                        }
                                                    }
                                                }
                                            }
                                        } else {
                                            if (features[4] <= 189.5) {
                                                if (features[2] <= 20.5) {
                                                    if (features[4] <= 186.5) {
                                                        if (features[2] <= 18.5) {
                                                            if (features[1] <= 737.0) {
                                                                epcpwm = 72.86363636363636;
                                                            } else {
                                                                epcpwm = 67.17692307692307;
                                                            }
                                                        } else {
                                                            if (features[1] <= 748.5) {
                                                                epcpwm = 66.6875;
                                                            } else {
                                                                if (features[1] <= 815.0) {
                                                                    epcpwm = 73.56;
                                                                } else {
                                                                    epcpwm = 64.0;
                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        if (features[2] <= 13.5) {
                                                            if (features[4] <= 188.5) {
                                                                epcpwm = 70.51724137931035;
                                                            } else {
                                                                epcpwm = 74.37837837837837;
                                                            }
                                                        } else {
                                                            if (features[0] <= 41.5) {
                                                                epcpwm = 71.1159420289855;
                                                            } else {
                                                                if (features[1] <= 774.5) {
                                                                    if (features[2] <= 14.5) {
                                                                        epcpwm = 60.22222222222222;
                                                                    } else {
                                                                        if (features[2] <= 17.5) {
                                                                            if (features[1] <= 754.5) {
                                                                                epcpwm = 74.11764705882354;
                                                                            } else {
                                                                                epcpwm = 60.0;
                                                                            }
                                                                        } else {
                                                                            epcpwm = 65.27027027027027;
                                                                        }
                                                                    }
                                                                } else {
                                                                    epcpwm = 69.93893129770993;
                                                                }
                                                            }
                                                        }
                                                    }
                                                } else {
                                                    if (features[4] <= 187.5) {
                                                        if (features[2] <= 23.5) {
                                                            epcpwm = 75.05791505791505;
                                                        } else {
                                                            epcpwm = 66.73333333333333;
                                                        }
                                                    } else {
                                                        if (features[1] <= 795.5) {
                                                            epcpwm = 64.52941176470588;
                                                        } else {
                                                            epcpwm = 72.0;
                                                        }
                                                    }
                                                }
                                            } else {
                                                if (features[1] <= 762.0) {
                                                    epcpwm = 63.08510638297872;
                                                } else {
                                                    epcpwm = 68.57142857142857;
                                                }
                                            }
                                        }
                                    } else {
                                        epcpwm = 63.58743169398907;
                                    }
                                } else {
                                    if (features[1] <= 1909.5) {
                                        if (features[3] <= 2.5) {
                                            if (features[1] <= 1042.5) {
                                                if (features[2] <= 14.5) {
                                                    if (features[2] <= 12.5) {
                                                        epcpwm = 68.32558139534883;
                                                    } else {
                                                        epcpwm = 63.917647058823526;
                                                    }
                                                } else {
                                                    epcpwm = 68.61363636363636;
                                                }
                                            } else {
                                                if (features[2] <= 13.5) {
                                                    if (features[1] <= 1240.5) {
                                                        if (features[4] <= 189.5) {
                                                            epcpwm = 64.07954545454545;
                                                        } else {
                                                            if (features[2] <= 12.5) {
                                                                epcpwm = 66.66666666666667;
                                                            } else {
                                                                epcpwm = 75.5;
                                                            }
                                                        }
                                                    } else {
                                                        if (features[1] <= 1593.0) {
                                                            if (features[1] <= 1502.0) {
                                                                if (features[1] <= 1445.5) {
                                                                    epcpwm = 69.3529411764706;
                                                                } else {
                                                                    epcpwm = 63.75;
                                                                }
                                                            } else {
                                                                if (features[4] <= 188.5) {
                                                                    epcpwm = 70.05263157894737;
                                                                } else {
                                                                    epcpwm = 77.05263157894737;
                                                                }
                                                            }
                                                        } else {
                                                            epcpwm = 66.44155844155844;
                                                        }
                                                    }
                                                } else {
                                                    if (features[4] <= 187.5) {
                                                        if (features[1] <= 1521.5) {
                                                            if (features[2] <= 14.5) {
                                                                epcpwm = 68.96078431372548;
                                                            } else {
                                                                if (features[4] <= 186.5) {
                                                                    epcpwm = 63.0940170940171;
                                                                } else {
                                                                    if (features[2] <= 17.5) {
                                                                        epcpwm = 63.955555555555556;
                                                                    } else {
                                                                        if (features[1] <= 1399.0) {
                                                                            if (features[0] <= 40.5) {
                                                                                epcpwm = 69.52777777777777;
                                                                            } else {
                                                                                epcpwm = 61.67857142857143;
                                                                            }
                                                                        } else {
                                                                            epcpwm = 71.81818181818181;
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        } else {
                                                            epcpwm = 63.105172413793106;
                                                        }
                                                    } else {
                                                        if (features[1] <= 1575.5) {
                                                            if (features[2] <= 18.5) {
                                                                if (features[2] <= 14.5) {
                                                                    if (features[0] <= 39.5) {
                                                                        epcpwm = 59.833333333333336;
                                                                    } else {
                                                                        if (features[1] <= 1465.0) {
                                                                            epcpwm = 69.02222222222223;
                                                                        } else {
                                                                            epcpwm = 59.4;
                                                                        }
                                                                    }
                                                                } else {
                                                                    epcpwm = 63.68600682593857;
                                                                }
                                                            } else {
                                                                if (features[1] <= 1220.5) {
                                                                    epcpwm = 68.34408602150538;
                                                                } else {
                                                                    epcpwm = 65.14;
                                                                }
                                                            }
                                                        } else {
                                                            if (features[1] <= 1641.5) {
                                                                if (features[2] <= 21.5) {
                                                                    if (features[4] <= 189.5) {
                                                                        if (features[1] <= 1597.0) {
                                                                            if (features[4] <= 188.5) {
                                                                                epcpwm = 75.0;
                                                                            } else {
                                                                                epcpwm = 65.3;
                                                                            }
                                                                        } else {
                                                                            epcpwm = 74.43243243243244;
                                                                        }
                                                                    } else {
                                                                        epcpwm = 63.916666666666664;
                                                                    }
                                                                } else {
                                                                    epcpwm = 63.46153846153846;
                                                                }
                                                            } else {
                                                                if (features[0] <= 40.5) {
                                                                    epcpwm = 64.43396226415095;
                                                                } else {
                                                                    if (features[4] <= 188.5) {
                                                                        if (features[2] <= 20.5) {
                                                                            if (features[0] <= 41.5) {
                                                                                epcpwm = 67.65217391304348;
                                                                            } else {
                                                                                epcpwm = 72.70454545454545;
                                                                            }
                                                                        } else {
                                                                            if (features[1] <= 1883.5) {
                                                                                epcpwm = 63.56521739130435;
                                                                            } else {
                                                                                epcpwm = 78.0;
                                                                            }
                                                                        }
                                                                    } else {
                                                                        epcpwm = 65.82386363636364;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        } else {
                                            if (features[2] <= 36.5) {
                                                if (features[3] <= 3.5) {
                                                    if (features[4] <= 187.5) {
                                                        epcpwm = 63.26832641770401;
                                                    } else {
                                                        epcpwm = 64.02135738016136;
                                                    }
                                                } else {
                                                    if (features[1] <= 1660.5) {
                                                        epcpwm = 64.65313653136532;
                                                    } else {
                                                        epcpwm = 68.10810810810811;
                                                    }
                                                }
                                            } else {
                                                if (features[4] <= 188.5) {
                                                    epcpwm = 66.00170357751277;
                                                } else {
                                                    epcpwm = 67.4;
                                                }
                                            }
                                        }
                                    } else {
                                        if (features[1] <= 2290.5) {
                                            if (features[2] <= 39.5) {
                                                if (features[3] <= 2.5) {
                                                    if (features[2] <= 21.5) {
                                                        epcpwm = 64.696;
                                                    } else {
                                                        if (features[1] <= 2185.0) {
                                                            if (features[1] <= 1986.0) {
                                                                if (features[2] <= 22.5) {
                                                                    if (features[4] <= 187.5) {
                                                                        if (features[0] <= 41.5) {
                                                                            epcpwm = 60.7;
                                                                        } else {
                                                                            epcpwm = 76.0;
                                                                        }
                                                                    } else {
                                                                        if (features[1] <= 1917.5) {
                                                                            epcpwm = 62.0;
                                                                        } else {
                                                                            epcpwm = 76.5;
                                                                        }
                                                                    }
                                                                } else {
                                                                    epcpwm = 63.212765957446805;
                                                                }
                                                            } else {
                                                                epcpwm = 69.08917197452229;
                                                            }
                                                        } else {
                                                            epcpwm = 64.7375;
                                                        }
                                                    }
                                                } else {
                                                    epcpwm = 64.54472843450479;
                                                }
                                            } else {
                                                epcpwm = 66.5455647955648;
                                            }
                                        } else {
                                            if (features[3] <= 2.5) {
                                                if (features[2] <= 26.5) {
                                                    if (features[4] <= 186.5) {
                                                        epcpwm = 70.53571428571429;
                                                    } else {
                                                        epcpwm = 63.61904761904762;
                                                    }
                                                } else {
                                                    if (features[0] <= 41.5) {
                                                        epcpwm = 75.21383647798743;
                                                    } else {
                                                        if (features[1] <= 2416.5) {
                                                            epcpwm = 75.71428571428571;
                                                        } else {
                                                            if (features[2] <= 30.5) {
                                                                epcpwm = 63.69230769230769;
                                                            } else {
                                                                epcpwm = 76.57142857142857;
                                                            }
                                                        }
                                                    }
                                                }
                                            } else {
                                                if (features[3] <= 3.5) {
                                                    epcpwm = 64.90434782608696;
                                                } else {
                                                    epcpwm = 67.40652173913044;
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (features[2] <= 39.5) {
                                    if (features[3] <= 2.5) {
                                        if (features[1] <= 1467.5) {
                                            if (features[1] <= 750.5) {
                                                if (features[2] <= 12.5) {
                                                    if (features[1] <= 701.5) {
                                                        epcpwm = 66.22972972972973;
                                                    } else {
                                                        if (features[4] <= 186.5) {
                                                            epcpwm = 63.0;
                                                        } else {
                                                            epcpwm = 71.97435897435898;
                                                        }
                                                    }
                                                } else {
                                                    if (features[1] <= 528.5) {
                                                        epcpwm = 77.0;
                                                    } else {
                                                        epcpwm = 65.88541666666667;
                                                    }
                                                }
                                            } else {
                                                if (features[1] <= 940.5) {
                                                    if (features[1] <= 781.5) {
                                                        if (features[4] <= 189.5) {
                                                            if (features[4] <= 188.5) {
                                                                if (features[1] <= 755.5) {
                                                                    epcpwm = 71.22727272727273;
                                                                } else {
                                                                    epcpwm = 66.98901098901099;
                                                                }
                                                            } else {
                                                                if (features[2] <= 16.5) {
                                                                    if (features[1] <= 778.5) {
                                                                        epcpwm = 73.75471698113208;
                                                                    } else {
                                                                        epcpwm = 64.5;
                                                                    }
                                                                } else {
                                                                    epcpwm = 67.14285714285714;
                                                                }
                                                            }
                                                        } else {
                                                            epcpwm = 64.4342105263158;
                                                        }
                                                    } else {
                                                        if (features[2] <= 12.5) {
                                                            epcpwm = 73.62857142857143;
                                                        } else {
                                                            epcpwm = 69.99409681227863;
                                                        }
                                                    }
                                                } else {
                                                    if (features[1] <= 1245.5) {
                                                        if (features[2] <= 16.5) {
                                                            if (features[1] <= 1229.5) {
                                                                epcpwm = 66.0622009569378;
                                                            } else {
                                                                epcpwm = 70.95454545454545;
                                                            }
                                                        } else {
                                                            if (features[1] <= 1224.0) {
                                                                epcpwm = 69.27665706051873;
                                                            } else {
                                                                if (features[2] <= 20.5) {
                                                                    epcpwm = 62.476190476190474;
                                                                } else {
                                                                    epcpwm = 71.71428571428571;
                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        if (features[2] <= 17.5) {
                                                            if (features[4] <= 188.5) {
                                                                epcpwm = 72.28125;
                                                            } else {
                                                                if (features[1] <= 1407.0) {
                                                                    epcpwm = 66.21621621621621;
                                                                } else {
                                                                    epcpwm = 70.93181818181819;
                                                                }
                                                            }
                                                        } else {
                                                            if (features[0] <= 45.5) {
                                                                epcpwm = 65.5;
                                                            } else {
                                                                if (features[4] <= 188.5) {
                                                                    if (features[4] <= 186.5) {
                                                                        epcpwm = 65.76923076923077;
                                                                    } else {
                                                                        epcpwm = 75.03703703703704;
                                                                    }
                                                                } else {
                                                                    epcpwm = 63.36363636363637;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        } else {
                                            if (features[2] <= 23.5) {
                                                if (features[4] <= 187.5) {
                                                    if (features[1] <= 1885.0) {
                                                        epcpwm = 65.1151919866444;
                                                    } else {
                                                        epcpwm = 66.77083333333333;
                                                    }
                                                } else {
                                                    epcpwm = 66.80968468468468;
                                                }
                                            } else {
                                                if (features[2] <= 31.5) {
                                                    if (features[1] <= 2586.5) {
                                                        if (features[1] <= 2010.5) {
                                                            epcpwm = 66.72289156626506;
                                                        } else {
                                                            if (features[4] <= 188.5) {
                                                                epcpwm = 70.79144385026738;
                                                            } else {
                                                                if (features[1] <= 2466.0) {
                                                                    epcpwm = 67.75806451612904;
                                                                } else {
                                                                    epcpwm = 53.0;
                                                                }
                                                            }
                                                        }
                                                    } else {
                                                        epcpwm = 65.13888888888889;
                                                    }
                                                } else {
                                                    epcpwm = 77.27272727272727;
                                                }
                                            }
                                        }
                                    } else {
                                        if (features[2] <= 30.5) {
                                            if (features[3] <= 3.5) {
                                                if (features[1] <= 1697.0) {
                                                    epcpwm = 65.58572247706422;
                                                } else {
                                                    epcpwm = 66.74636510500808;
                                                }
                                            } else {
                                                epcpwm = 67.24691358024691;
                                            }
                                        } else {
                                            epcpwm = 66.95114942528735;
                                        }
                                    }
                                } else {
                                    if (features[1] <= 2203.5) {
                                        if (features[4] <= 188.5) {
                                            if (features[3] <= 3.5) {
                                                epcpwm = 64.6774193548387;
                                            } else {
                                                epcpwm = 68.16059479553904;
                                            }
                                        } else {
                                            if (features[1] <= 1449.5) {
                                                if (features[4] <= 189.5) {
                                                    epcpwm = 67.6923076923077;
                                                } else {
                                                    epcpwm = 74.84615384615384;
                                                }
                                            } else {
                                                epcpwm = 68.62307967131119;
                                            }
                                        }
                                    } else {
                                        if (features[2] <= 62.5) {
                                            epcpwm = 68.84038199181447;
                                        } else {
                                            epcpwm = 70.2713567839196;
                                        }
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[0] <= 42.5) {
                        if (features[1] <= 813.5) {
                            if (features[3] <= 2.5) {
                                if (features[1] <= 718.5) {
                                    if (features[2] <= 17.5) {
                                        epcpwm = 73.01052631578948;
                                    } else {
                                        if (features[1] <= 702.0) {
                                            epcpwm = 70.7;
                                        } else {
                                            epcpwm = 61.285714285714285;
                                        }
                                    }
                                } else {
                                    epcpwm = 74.60243407707911;
                                }
                            } else {
                                epcpwm = 63.353846153846156;
                            }
                        } else {
                            if (features[2] <= 48.5) {
                                if (features[3] <= 2.5) {
                                    if (features[4] <= 192.5) {
                                        if (features[1] <= 1054.5) {
                                            epcpwm = 71.97321428571429;
                                        } else {
                                            if (features[2] <= 21.5) {
                                                if (features[4] <= 191.5) {
                                                    if (features[2] <= 11.5) {
                                                        if (features[1] <= 1300.0) {
                                                            epcpwm = 65.11428571428571;
                                                        } else {
                                                            if (features[1] <= 1525.0) {
                                                                epcpwm = 73.25;
                                                            } else {
                                                                epcpwm = 62.2;
                                                            }
                                                        }
                                                    } else {
                                                        epcpwm = 65.2014652014652;
                                                    }
                                                } else {
                                                    if (features[2] <= 6.0) {
                                                        epcpwm = 73.42857142857143;
                                                    } else {
                                                        if (features[1] <= 1797.5) {
                                                            epcpwm = 62.13333333333333;
                                                        } else {
                                                            if (features[1] <= 1832.0) {
                                                                epcpwm = 78.0;
                                                            } else {
                                                                epcpwm = 65.8125;
                                                            }
                                                        }
                                                    }
                                                }
                                            } else {
                                                if (features[1] <= 2008.0) {
                                                    epcpwm = 74.93846153846154;
                                                } else {
                                                    epcpwm = 64.39285714285714;
                                                }
                                            }
                                        }
                                    } else {
                                        if (features[2] <= 17.5) {
                                            if (features[2] <= 7.5) {
                                                if (features[4] <= 193.5) {
                                                    epcpwm = 74.50769230769231;
                                                } else {
                                                    epcpwm = 60.0;
                                                }
                                            } else {
                                                if (features[4] <= 194.5) {
                                                    if (features[4] <= 193.5) {
                                                        if (features[2] <= 10.5) {
                                                            epcpwm = 71.48717948717949;
                                                        } else {
                                                            if (features[1] <= 1349.0) {
                                                                epcpwm = 65.25675675675676;
                                                            } else {
                                                                epcpwm = 69.35897435897436;
                                                            }
                                                        }
                                                    } else {
                                                        if (features[2] <= 10.0) {
                                                            epcpwm = 63.44444444444444;
                                                        } else {
                                                            epcpwm = 72.98148148148148;
                                                        }
                                                    }
                                                } else {
                                                    epcpwm = 64.95652173913044;
                                                }
                                            }
                                        } else {
                                            epcpwm = 73.25249169435216;
                                        }
                                    }
                                } else {
                                    if (features[2] <= 38.5) {
                                        if (features[2] <= 28.5) {
                                            epcpwm = 64.91326530612245;
                                        } else {
                                            epcpwm = 66.20786092214664;
                                        }
                                    } else {
                                        if (features[1] <= 1828.5) {
                                            epcpwm = 68.70884871550903;
                                        } else {
                                            if (features[1] <= 2399.0) {
                                                if (features[1] <= 2199.5) {
                                                    epcpwm = 67.56746532156369;
                                                } else {
                                                    if (features[1] <= 2315.0) {
                                                        if (features[2] <= 47.5) {
                                                            epcpwm = 65.51271186440678;
                                                        } else {
                                                            if (features[1] <= 2286.5) {
                                                                epcpwm = 54.63636363636363;
                                                            } else {
                                                                epcpwm = 64.02941176470588;
                                                            }
                                                        }
                                                    } else {
                                                        epcpwm = 67.2896174863388;
                                                    }
                                                }
                                            } else {
                                                epcpwm = 69.26178010471205;
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (features[1] <= 2166.5) {
                                    if (features[1] <= 2069.5) {
                                        if (features[0] <= 41.5) {
                                            if (features[4] <= 193.5) {
                                                epcpwm = 70.2332838038633;
                                            } else {
                                                epcpwm = 69.51539855072464;
                                            }
                                        } else {
                                            epcpwm = 70.76348228043143;
                                        }
                                    } else {
                                        if (features[4] <= 191.5) {
                                            epcpwm = 67.42618384401115;
                                        } else {
                                            if (features[2] <= 51.5) {
                                                epcpwm = 67.76923076923077;
                                            } else {
                                                epcpwm = 69.74571686203787;
                                            }
                                        }
                                    }
                                } else {
                                    if (features[1] <= 2404.5) {
                                        if (features[2] <= 59.5) {
                                            if (features[4] <= 191.5) {
                                                if (features[1] <= 2219.5) {
                                                    if (features[2] <= 56.5) {
                                                        epcpwm = 66.96268656716418;
                                                    } else {
                                                        if (features[1] <= 2188.5) {
                                                            epcpwm = 66.34285714285714;
                                                        } else {
                                                            epcpwm = 63.18018018018018;
                                                        }
                                                    }
                                                } else {
                                                    epcpwm = 67.20982142857143;
                                                }
                                            } else {
                                                if (features[0] <= 40.5) {
                                                    epcpwm = 67.03881578947369;
                                                } else {
                                                    epcpwm = 67.70588235294117;
                                                }
                                            }
                                        } else {
                                            epcpwm = 67.92078681552366;
                                        }
                                    } else {
                                        if (features[1] <= 2642.0) {
                                            epcpwm = 69.77460629921259;
                                        } else {
                                            epcpwm = 64.13333333333334;
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (features[2] <= 46.5) {
                            if (features[3] <= 2.5) {
                                if (features[1] <= 1044.5) {
                                    if (features[1] <= 624.0) {
                                        if (features[1] <= 546.0) {
                                            epcpwm = 53.5;
                                        } else {
                                            epcpwm = 66.72727272727273;
                                        }
                                    } else {
                                        if (features[2] <= 11.5) {
                                            if (features[4] <= 191.5) {
                                                if (features[1] <= 718.0) {
                                                    if (features[2] <= 7.5) {
                                                        epcpwm = 74.0;
                                                    } else {
                                                        epcpwm = 66.79310344827586;
                                                    }
                                                } else {
                                                    epcpwm = 73.03508771929825;
                                                }
                                            } else {
                                                if (features[4] <= 193.5) {
                                                    epcpwm = 74.91791044776119;
                                                } else {
                                                    if (features[0] <= 44.5) {
                                                        epcpwm = 74.6923076923077;
                                                    } else {
                                                        epcpwm = 64.33333333333333;
                                                    }
                                                }
                                            }
                                        } else {
                                            if (features[2] <= 20.5) {
                                                if (features[4] <= 191.5) {
                                                    if (features[1] <= 773.5) {
                                                        epcpwm = 65.82089552238806;
                                                    } else {
                                                        if (features[2] <= 14.5) {
                                                            if (features[1] <= 840.5) {
                                                                epcpwm = 74.0;
                                                            } else {
                                                                epcpwm = 63.61538461538461;
                                                            }
                                                        } else {
                                                            epcpwm = 73.5;
                                                        }
                                                    }
                                                } else {
                                                    if (features[1] <= 821.5) {
                                                        if (features[1] <= 794.5) {
                                                            epcpwm = 71.76506024096386;
                                                        } else {
                                                            epcpwm = 77.19047619047619;
                                                        }
                                                    } else {
                                                        if (features[4] <= 192.5) {
                                                            epcpwm = 66.27027027027027;
                                                        } else {
                                                            if (features[1] <= 1003.5) {
                                                                if (features[2] <= 13.5) {
                                                                    epcpwm = 67.10714285714286;
                                                                } else {
                                                                    epcpwm = 72.47826086956522;
                                                                }
                                                            } else {
                                                                epcpwm = 76.0;
                                                            }
                                                        }
                                                    }
                                                }
                                            } else {
                                                if (features[1] <= 741.0) {
                                                    epcpwm = 65.83333333333333;
                                                } else {
                                                    epcpwm = 75.96385542168674;
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[4] <= 192.5) {
                                        if (features[2] <= 21.5) {
                                            if (features[2] <= 12.5) {
                                                if (features[4] <= 191.5) {
                                                    if (features[1] <= 1210.0) {
                                                        epcpwm = 66.16666666666667;
                                                    } else {
                                                        epcpwm = 72.94545454545455;
                                                    }
                                                } else {
                                                    epcpwm = 67.54285714285714;
                                                }
                                            } else {
                                                epcpwm = 66.33421052631579;
                                            }
                                        } else {
                                            if (features[1] <= 1916.5) {
                                                if (features[0] <= 45.5) {
                                                    epcpwm = 77.28125;
                                                } else {
                                                    epcpwm = 69.44444444444444;
                                                }
                                            } else {
                                                epcpwm = 67.3409090909091;
                                            }
                                        }
                                    } else {
                                        if (features[4] <= 194.5) {
                                            if (features[2] <= 23.5) {
                                                epcpwm = 71.17788461538461;
                                            } else {
                                                epcpwm = 75.52173913043478;
                                            }
                                        } else {
                                            epcpwm = 65.91891891891892;
                                        }
                                    }
                                }
                            } else {
                                if (features[2] <= 28.5) {
                                    if (features[4] <= 192.5) {
                                        epcpwm = 66.11650485436893;
                                    } else {
                                        epcpwm = 67.23404255319149;
                                    }
                                } else {
                                    if (features[2] <= 39.5) {
                                        if (features[1] <= 393.5) {
                                            epcpwm = 76.66666666666667;
                                        } else {
                                            epcpwm = 68.26080084299262;
                                        }
                                    } else {
                                        if (features[1] <= 2583.0) {
                                            if (features[1] <= 1766.0) {
                                                epcpwm = 70.3078231292517;
                                            } else {
                                                if (features[3] <= 3.5) {
                                                    epcpwm = 69.76119402985074;
                                                } else {
                                                    if (features[4] <= 197.5) {
                                                        epcpwm = 68.62711864406779;
                                                    } else {
                                                        if (features[0] <= 45.5) {
                                                            epcpwm = 67.44444444444444;
                                                        } else {
                                                            epcpwm = 50.0;
                                                        }
                                                    }
                                                }
                                            }
                                        } else {
                                            epcpwm = 71.43506493506493;
                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[1] <= 2161.5) {
                                if (features[4] <= 191.5) {
                                    if (features[1] <= 2062.5) {
                                        if (features[1] <= 1890.0) {
                                            if (features[2] <= 50.5) {
                                                epcpwm = 71.06341463414634;
                                            } else {
                                                epcpwm = 67.02439024390245;
                                            }
                                        } else {
                                            epcpwm = 72.26636568848758;
                                        }
                                    } else {
                                        epcpwm = 69.06763285024155;
                                    }
                                } else {
                                    if (features[4] <= 194.5) {
                                        if (features[2] <= 48.5) {
                                            epcpwm = 70.2663043478261;
                                        } else {
                                            if (features[1] <= 2034.5) {
                                                if (features[1] <= 2003.5) {
                                                    if (features[2] <= 51.5) {
                                                        if (features[1] <= 1844.5) {
                                                            epcpwm = 69.50980392156863;
                                                        } else {
                                                            epcpwm = 72.69025367156209;
                                                        }
                                                    } else {
                                                        epcpwm = 70.8955223880597;
                                                    }
                                                } else {
                                                    epcpwm = 73.47095761381476;
                                                }
                                            } else {
                                                if (features[0] <= 45.5) {
                                                    if (features[2] <= 50.5) {
                                                        epcpwm = 68.52173913043478;
                                                    } else {
                                                        if (features[2] <= 57.5) {
                                                            epcpwm = 71.63201530612245;
                                                        } else {
                                                            epcpwm = 72.95238095238095;
                                                        }
                                                    }
                                                } else {
                                                    epcpwm = 72.50836120401338;
                                                }
                                            }
                                        }
                                    } else {
                                        if (features[4] <= 196.5) {
                                            epcpwm = 71.34661791590493;
                                        } else {
                                            epcpwm = 70.12323943661971;
                                        }
                                    }
                                }
                            } else {
                                if (features[1] <= 2423.5) {
                                    if (features[0] <= 43.5) {
                                        epcpwm = 68.92655059847661;
                                    } else {
                                        if (features[4] <= 192.5) {
                                            epcpwm = 69.29469387755103;
                                        } else {
                                            if (features[2] <= 48.5) {
                                                if (features[1] <= 2384.5) {
                                                    epcpwm = 68.08363636363636;
                                                } else {
                                                    epcpwm = 70.70642201834862;
                                                }
                                            } else {
                                                if (features[1] <= 2169.5) {
                                                    epcpwm = 71.09225092250922;
                                                } else {
                                                    epcpwm = 69.88172909115318;
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[2] <= 60.5) {
                                        if (features[4] <= 196.5) {
                                            if (features[1] <= 2597.5) {
                                                epcpwm = 71.83742400360279;
                                            } else {
                                                epcpwm = 69.3048780487805;
                                            }
                                        } else {
                                            epcpwm = 70.6798866855524;
                                        }
                                    } else {
                                        epcpwm = 68.0958904109589;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        if (features[0] <= 53.5) {
            if (features[2] <= 40.5) {
                if (features[3] <= 1.5) {
                    if (features[1] <= 838.5) {
                        if (features[1] <= 629.5) {
                            epcpwm = 75.97254901960784;
                        } else {
                            if (features[1] <= 699.5) {
                                if (features[4] <= 185.5) {
                                    epcpwm = 70.96428571428571;
                                } else {
                                    if (features[2] <= 7.5) {
                                        epcpwm = 75.42541436464089;
                                    } else {
                                        if (features[1] <= 695.5) {
                                            if (features[0] <= 52.5) {
                                                epcpwm = 73.39375;
                                            } else {
                                                epcpwm = 62.0;
                                            }
                                        } else {
                                            if (features[0] <= 49.5) {
                                                epcpwm = 69.33333333333333;
                                            } else {
                                                epcpwm = 54.0;
                                            }
                                        }
                                    }
                                }
                            } else {
                                epcpwm = 75.10174418604652;
                            }
                        }
                    } else {
                        epcpwm = 77.20582524271845;
                    }
                } else {
                    if (features[4] <= 185.5) {
                        if (features[4] <= 183.5) {
                            if (features[2] <= 18.5) {
                                if (features[0] <= 49.5) {
                                    epcpwm = 65.4921875;
                                } else {
                                    epcpwm = 66.27924340467895;
                                }
                            } else {
                                if (features[0] <= 49.5) {
                                    if (features[1] <= 1193.5) {
                                        if (features[3] <= 2.5) {
                                            if (features[2] <= 21.5) {
                                                if (features[4] <= 178.5) {
                                                    epcpwm = 62.083333333333336;
                                                } else {
                                                    epcpwm = 68.39805825242719;
                                                }
                                            } else {
                                                epcpwm = 74.875;
                                            }
                                        } else {
                                            epcpwm = 66.08148148148148;
                                        }
                                    } else {
                                        epcpwm = 65.89420289855073;
                                    }
                                } else {
                                    epcpwm = 67.14015748031495;
                                }
                            }
                        } else {
                            if (features[1] <= 813.5) {
                                epcpwm = 66.34943977591037;
                            } else {
                                if (features[2] <= 27.5) {
                                    if (features[3] <= 3.5) {
                                        epcpwm = 67.25907065563335;
                                    } else {
                                        epcpwm = 69.6590909090909;
                                    }
                                } else {
                                    epcpwm = 68.06788511749347;
                                }
                            }
                        }
                    } else {
                        if (features[1] <= 734.5) {
                            if (features[1] <= 564.5) {
                                if (features[4] <= 192.5) {
                                    epcpwm = 64.30357142857143;
                                } else {
                                    epcpwm = 59.22222222222222;
                                }
                            } else {
                                if (features[1] <= 678.5) {
                                    epcpwm = 66.72602040816327;
                                } else {
                                    if (features[2] <= 12.5) {
                                        if (features[1] <= 688.5) {
                                            epcpwm = 71.22388059701493;
                                        } else {
                                            epcpwm = 68.43457943925233;
                                        }
                                    } else {
                                        epcpwm = 67.33492496589359;
                                    }
                                }
                            }
                        } else {
                            if (features[4] <= 190.5) {
                                if (features[4] <= 187.5) {
                                    if (features[0] <= 50.5) {
                                        if (features[1] <= 2094.5) {
                                            if (features[1] <= 902.5) {
                                                if (features[3] <= 2.5) {
                                                    if (features[1] <= 785.5) {
                                                        epcpwm = 67.95330739299611;
                                                    } else {
                                                        epcpwm = 70.2639405204461;
                                                    }
                                                } else {
                                                    epcpwm = 67.42168674698796;
                                                }
                                            } else {
                                                epcpwm = 67.65363681345869;
                                            }
                                        } else {
                                            if (features[2] <= 19.5) {
                                                epcpwm = 75.38888888888889;
                                            } else {
                                                epcpwm = 68.49875311720699;
                                            }
                                        }
                                    } else {
                                        if (features[2] <= 20.5) {
                                            epcpwm = 68.13865096359743;
                                        } else {
                                            epcpwm = 68.92415076779898;
                                        }
                                    }
                                } else {
                                    if (features[2] <= 9.5) {
                                        if (features[1] <= 1426.0) {
                                            if (features[4] <= 189.5) {
                                                epcpwm = 74.25139664804469;
                                            } else {
                                                if (features[0] <= 47.5) {
                                                    epcpwm = 64.0;
                                                } else {
                                                    if (features[1] <= 1192.0) {
                                                        epcpwm = 72.63157894736842;
                                                    } else {
                                                        epcpwm = 65.9375;
                                                    }
                                                }
                                            }
                                        } else {
                                            epcpwm = 66.91578947368421;
                                        }
                                    } else {
                                        if (features[2] <= 30.5) {
                                            if (features[0] <= 51.5) {
                                                if (features[1] <= 881.5) {
                                                    if (features[2] <= 14.5) {
                                                        if (features[3] <= 2.5) {
                                                            epcpwm = 72.69458128078817;
                                                        } else {
                                                            epcpwm = 68.19607843137256;
                                                        }
                                                    } else {
                                                        if (features[1] <= 800.5) {
                                                            epcpwm = 67.6820809248555;
                                                        } else {
                                                            if (features[3] <= 2.5) {
                                                                if (features[1] <= 853.5) {
                                                                    epcpwm = 69.93548387096774;
                                                                } else {
                                                                    epcpwm = 72.83720930232558;
                                                                }
                                                            } else {
                                                                epcpwm = 67.72093023255815;
                                                            }
                                                        }
                                                    }
                                                } else {
                                                    epcpwm = 68.26429601153292;
                                                }
                                            } else {
                                                if (features[1] <= 763.5) {
                                                    epcpwm = 66.86764705882354;
                                                } else {
                                                    epcpwm = 68.94949856733524;
                                                }
                                            }
                                        } else {
                                            if (features[0] <= 50.5) {
                                                epcpwm = 69.00730307772561;
                                            } else {
                                                epcpwm = 69.87994808565867;
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (features[2] <= 28.5) {
                                    if (features[4] <= 192.5) {
                                        if (features[2] <= 7.5) {
                                            if (features[1] <= 1064.5) {
                                                epcpwm = 73.83333333333333;
                                            } else {
                                                epcpwm = 68.96969696969697;
                                            }
                                        } else {
                                            if (features[3] <= 3.5) {
                                                epcpwm = 68.86986955138403;
                                            } else {
                                                epcpwm = 70.8359375;
                                            }
                                        }
                                    } else {
                                        if (features[3] <= 2.5) {
                                            if (features[1] <= 1842.0) {
                                                if (features[0] <= 48.5) {
                                                    epcpwm = 72.33196721311475;
                                                } else {
                                                    if (features[1] <= 901.5) {
                                                        epcpwm = 68.83193277310924;
                                                    } else {
                                                        if (features[1] <= 1123.0) {
                                                            if (features[1] <= 993.0) {
                                                                if (features[0] <= 49.5) {
                                                                    epcpwm = 75.94117647058823;
                                                                } else {
                                                                    epcpwm = 69.28985507246377;
                                                                }
                                                            } else {
                                                                epcpwm = 75.65454545454546;
                                                            }
                                                        } else {
                                                            epcpwm = 70.15272727272728;
                                                        }
                                                    }
                                                }
                                            } else {
                                                epcpwm = 68.92307692307692;
                                            }
                                        } else {
                                            if (features[0] <= 48.5) {
                                                epcpwm = 68.7378640776699;
                                            } else {
                                                epcpwm = 69.88425196850393;
                                            }
                                        }
                                    }
                                } else {
                                    if (features[0] <= 51.5) {
                                        if (features[1] <= 2353.0) {
                                            epcpwm = 69.72435064935065;
                                        } else {
                                            epcpwm = 71.06020066889631;
                                        }
                                    } else {
                                        epcpwm = 70.98577844311377;
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[4] <= 191.5) {
                    if (features[0] <= 50.5) {
                        if (features[2] <= 49.5) {
                            if (features[4] <= 190.5) {
                                epcpwm = 69.44389875330563;
                            } else {
                                if (features[1] <= 1884.0) {
                                    epcpwm = 71.9572072072072;
                                } else {
                                    epcpwm = 69.62028301886792;
                                }
                            }
                        } else {
                            if (features[4] <= 190.5) {
                                if (features[0] <= 48.5) {
                                    epcpwm = 70.39043049792531;
                                } else {
                                    if (features[2] <= 52.5) {
                                        epcpwm = 70.4843408594319;
                                    } else {
                                        epcpwm = 70.93011600928074;
                                    }
                                }
                            } else {
                                if (features[1] <= 2071.0) {
                                    if (features[1] <= 1861.0) {
                                        epcpwm = 69.72413793103448;
                                    } else {
                                        epcpwm = 73.46181818181819;
                                    }
                                } else {
                                    if (features[2] <= 54.5) {
                                        if (features[1] <= 2453.5) {
                                            epcpwm = 70.10011778563015;
                                        } else {
                                            epcpwm = 72.75968992248062;
                                        }
                                    } else {
                                        if (features[0] <= 48.5) {
                                            epcpwm = 70.8253652058433;
                                        } else {
                                            epcpwm = 71.60589569160997;
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (features[2] <= 49.5) {
                            if (features[4] <= 190.5) {
                                epcpwm = 70.28994413407821;
                            } else {
                                if (features[1] <= 1817.5) {
                                    epcpwm = 73.05660377358491;
                                } else {
                                    epcpwm = 70.76863753213368;
                                }
                            }
                        } else {
                            if (features[4] <= 190.5) {
                                if (features[4] <= 185.5) {
                                    epcpwm = 70.68123667377398;
                                } else {
                                    if (features[0] <= 51.5) {
                                        epcpwm = 71.33575687072852;
                                    } else {
                                        epcpwm = 71.70135685210312;
                                    }
                                }
                            } else {
                                if (features[1] <= 2053.5) {
                                    if (features[1] <= 1873.0) {
                                        epcpwm = 71.2;
                                    } else {
                                        if (features[2] <= 50.5) {
                                            epcpwm = 76.76829268292683;
                                        } else {
                                            epcpwm = 73.91983122362869;
                                        }
                                    }
                                } else {
                                    epcpwm = 71.99103139013452;
                                }
                            }
                        }
                    }
                } else {
                    if (features[2] <= 48.5) {
                        if (features[1] <= 2700.0) {
                            if (features[0] <= 51.5) {
                                if (features[4] <= 195.5) {
                                    if (features[1] <= 1853.0) {
                                        if (features[2] <= 41.5) {
                                            if (features[1] <= 1558.0) {
                                                epcpwm = 71.00892857142857;
                                            } else {
                                                epcpwm = 67.72058823529412;
                                            }
                                        } else {
                                            epcpwm = 71.76696542893725;
                                        }
                                    } else {
                                        if (features[1] <= 2142.5) {
                                            epcpwm = 69.64102564102564;
                                        } else {
                                            epcpwm = 70.72056338028169;
                                        }
                                    }
                                } else {
                                    if (features[1] <= 2390.0) {
                                        epcpwm = 71.07207207207207;
                                    } else {
                                        epcpwm = 73.4770642201835;
                                    }
                                }
                            } else {
                                epcpwm = 71.94252873563218;
                            }
                        } else {
                            epcpwm = 73.657824933687;
                        }
                    } else {
                        if (features[1] <= 2070.5) {
                            if (features[4] <= 195.5) {
                                if (features[0] <= 51.5) {
                                    if (features[1] <= 1892.5) {
                                        epcpwm = 72.90789473684211;
                                    } else {
                                        if (features[2] <= 51.5) {
                                            if (features[4] <= 193.5) {
                                                if (features[1] <= 1960.5) {
                                                    epcpwm = 74.46084337349397;
                                                } else {
                                                    epcpwm = 75.49171974522292;
                                                }
                                            } else {
                                                epcpwm = 74.14758620689655;
                                            }
                                        } else {
                                            if (features[1] <= 2003.5) {
                                                epcpwm = 73.08617234468937;
                                            } else {
                                                if (features[1] <= 2032.5) {
                                                    epcpwm = 75.07462686567165;
                                                } else {
                                                    epcpwm = 73.99600798403193;
                                                }
                                            }
                                        }
                                    }
                                } else {
                                    if (features[1] <= 1854.5) {
                                        epcpwm = 71.35714285714286;
                                    } else {
                                        epcpwm = 75.17804323094425;
                                    }
                                }
                            } else {
                                epcpwm = 72.58713136729223;
                            }
                        } else {
                            if (features[1] <= 2427.5) {
                                if (features[1] <= 2164.5) {
                                    if (features[2] <= 51.5) {
                                        epcpwm = 70.47058823529412;
                                    } else {
                                        if (features[1] <= 2098.5) {
                                            if (features[4] <= 192.5) {
                                                epcpwm = 71.56338028169014;
                                            } else {
                                                if (features[4] <= 195.5) {
                                                    epcpwm = 72.94763406940064;
                                                } else {
                                                    epcpwm = 71.67777777777778;
                                                }
                                            }
                                        } else {
                                            if (features[0] <= 50.5) {
                                                if (features[4] <= 197.5) {
                                                    epcpwm = 73.40323359073359;
                                                } else {
                                                    epcpwm = 69.6896551724138;
                                                }
                                            } else {
                                                epcpwm = 74.08799012040754;
                                            }
                                        }
                                    }
                                } else {
                                    if (features[0] <= 51.5) {
                                        if (features[0] <= 49.5) {
                                            if (features[2] <= 54.5) {
                                                if (features[1] <= 2374.5) {
                                                    epcpwm = 70.60158835208472;
                                                } else {
                                                    epcpwm = 71.90238095238095;
                                                }
                                            } else {
                                                if (features[4] <= 193.5) {
                                                    epcpwm = 71.4617269984917;
                                                } else {
                                                    epcpwm = 71.85516739446871;
                                                }
                                            }
                                        } else {
                                            if (features[2] <= 54.5) {
                                                if (features[1] <= 2351.5) {
                                                    epcpwm = 70.82976190476191;
                                                } else {
                                                    epcpwm = 72.41804511278195;
                                                }
                                            } else {
                                                epcpwm = 72.36461414358699;
                                            }
                                        }
                                    } else {
                                        if (features[0] <= 52.5) {
                                            epcpwm = 72.77928618349026;
                                        } else {
                                            epcpwm = 73.32765363128492;
                                        }
                                    }
                                }
                            } else {
                                if (features[1] <= 2570.5) {
                                    if (features[0] <= 49.5) {
                                        if (features[2] <= 58.5) {
                                            if (features[4] <= 196.5) {
                                                epcpwm = 73.57262180974477;
                                            } else {
                                                epcpwm = 72.30981595092024;
                                            }
                                        } else {
                                            epcpwm = 71.16666666666667;
                                        }
                                    } else {
                                        if (features[2] <= 59.5) {
                                            if (features[1] <= 2504.5) {
                                                if (features[2] <= 50.5) {
                                                    epcpwm = 74.66773504273505;
                                                } else {
                                                    epcpwm = 73.82437150837988;
                                                }
                                            } else {
                                                epcpwm = 74.66950233943003;
                                            }
                                        } else {
                                            epcpwm = 71.50442477876106;
                                        }
                                    }
                                } else {
                                    epcpwm = 71.31353135313532;
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if (features[2] <= 32.5) {
                if (features[0] <= 61.5) {
                    if (features[0] <= 57.5) {
                        if (features[2] <= 19.5) {
                            if (features[1] <= 774.5) {
                                if (features[3] <= 2.5) {
                                    if (features[3] <= 1.5) {
                                        if (features[4] <= 192.5) {
                                            if (features[4] <= 186.5) {
                                                epcpwm = 65.5;
                                            } else {
                                                if (features[0] <= 54.5) {
                                                    epcpwm = 67.0;
                                                } else {
                                                    epcpwm = 55.05555555555556;
                                                }
                                            }
                                        } else {
                                            epcpwm = 78.5;
                                        }
                                    } else {
                                        epcpwm = 67.9010384850336;
                                    }
                                } else {
                                    epcpwm = 69.85192697768763;
                                }
                            } else {
                                if (features[4] <= 184.5) {
                                    if (features[3] <= 1.5) {
                                        if (features[2] <= 16.0) {
                                            epcpwm = 77.9047619047619;
                                        } else {
                                            epcpwm = 59.0;
                                        }
                                    } else {
                                        epcpwm = 68.59452887537994;
                                    }
                                } else {
                                    if (features[4] <= 190.5) {
                                        epcpwm = 69.8043748446433;
                                    } else {
                                        epcpwm = 70.97969991173875;
                                    }
                                }
                            }
                        } else {
                            if (features[4] <= 190.5) {
                                if (features[4] <= 184.5) {
                                    if (features[3] <= 1.5) {
                                        epcpwm = 79.0;
                                    } else {
                                        epcpwm = 69.27537796976242;
                                    }
                                } else {
                                    if (features[1] <= 1470.5) {
                                        if (features[3] <= 3.5) {
                                            if (features[1] <= 863.0) {
                                                if (features[2] <= 29.0) {
                                                    epcpwm = 68.1198347107438;
                                                } else {
                                                    epcpwm = 77.0;
                                                }
                                            } else {
                                                epcpwm = 70.25460780111445;
                                            }
                                        } else {
                                            epcpwm = 72.06388888888888;
                                        }
                                    } else {
                                        epcpwm = 71.35078125;
                                    }
                                }
                            } else {
                                if (features[3] <= 3.5) {
                                    if (features[1] <= 1699.5) {
                                        epcpwm = 71.39277297721917;
                                    } else {
                                        epcpwm = 72.74034334763948;
                                    }
                                } else {
                                    epcpwm = 73.4304347826087;
                                }
                            }
                        }
                    } else {
                        if (features[3] <= 2.5) {
                            if (features[1] <= 1022.5) {
                                if (features[4] <= 191.5) {
                                    if (features[1] <= 1020.5) {
                                        epcpwm = 69.67350993377484;
                                    } else {
                                        if (features[0] <= 60.0) {
                                            epcpwm = 70.66666666666667;
                                        } else {
                                            epcpwm = 51.0;
                                        }
                                    }
                                } else {
                                    epcpwm = 72.3972602739726;
                                }
                            } else {
                                if (features[4] <= 187.5) {
                                    if (features[1] <= 1500.5) {
                                        if (features[3] <= 1.5) {
                                            epcpwm = 78.375;
                                        } else {
                                            epcpwm = 70.5409974640744;
                                        }
                                    } else {
                                        epcpwm = 71.58640636297903;
                                    }
                                } else {
                                    if (features[1] <= 1586.5) {
                                        epcpwm = 71.72821100917432;
                                    } else {
                                        if (features[2] <= 17.5) {
                                            epcpwm = 71.88235294117646;
                                        } else {
                                            if (features[4] <= 189.5) {
                                                epcpwm = 72.76829268292683;
                                            } else {
                                                epcpwm = 74.41875;
                                            }
                                        }
                                    }
                                }
                            }
                        } else {
                            if (features[4] <= 185.5) {
                                if (features[1] <= 1594.5) {
                                    epcpwm = 71.13849958779885;
                                } else {
                                    epcpwm = 72.62191780821918;
                                }
                            } else {
                                if (features[1] <= 1524.5) {
                                    if (features[3] <= 3.5) {
                                        if (features[4] <= 192.5) {
                                            epcpwm = 72.39786921381338;
                                        } else {
                                            epcpwm = 73.9038961038961;
                                        }
                                    } else {
                                        epcpwm = 74.35917312661499;
                                    }
                                } else {
                                    if (features[4] <= 189.5) {
                                        epcpwm = 73.43508424182359;
                                    } else {
                                        epcpwm = 74.43305785123967;
                                    }
                                }
                            }
                        }
                    }
                } else {
                    if (features[0] <= 65.5) {
                        if (features[3] <= 2.5) {
                            if (features[1] <= 1355.5) {
                                if (features[1] <= 1022.5) {
                                    if (features[2] <= 5.5) {
                                        epcpwm = 66.5;
                                    } else {
                                        epcpwm = 71.36468885672937;
                                    }
                                } else {
                                    if (features[4] <= 189.5) {
                                        epcpwm = 72.29796511627907;
                                    } else {
                                        epcpwm = 74.6390977443609;
                                    }
                                }
                            } else {
                                if (features[4] <= 186.5) {
                                    epcpwm = 73.22716248989491;
                                } else {
                                    epcpwm = 74.44679186228483;
                                }
                            }
                        } else {
                            if (features[4] <= 190.5) {
                                if (features[0] <= 63.5) {
                                    if (features[1] <= 679.5) {
                                        epcpwm = 54.714285714285715;
                                    } else {
                                        if (features[4] <= 185.5) {
                                            epcpwm = 73.5062034739454;
                                        } else {
                                            epcpwm = 74.52707373271889;
                                        }
                                    }
                                } else {
                                    epcpwm = 74.83791125867793;
                                }
                            } else {
                                if (features[1] <= 1442.5) {
                                    epcpwm = 74.99058380414313;
                                } else {
                                    epcpwm = 76.48453608247422;
                                }
                            }
                        }
                    } else {
                        if (features[3] <= 1.5) {
                            if (features[1] <= 913.0) {
                                epcpwm = 59.21739130434783;
                            } else {
                                epcpwm = 79.0;
                            }
                        } else {
                            if (features[0] <= 82.5) {
                                if (features[0] <= 69.5) {
                                    if (features[4] <= 184.5) {
                                        epcpwm = 74.7753209700428;
                                    } else {
                                        if (features[3] <= 2.5) {
                                            if (features[1] <= 1219.5) {
                                                if (features[2] <= 6.5) {
                                                    epcpwm = 67.0;
                                                } else {
                                                    epcpwm = 74.17320261437908;
                                                }
                                            } else {
                                                epcpwm = 75.82178988326848;
                                            }
                                        } else {
                                            epcpwm = 76.54061757719715;
                                        }
                                    }
                                } else {
                                    if (features[2] <= 14.5) {
                                        if (features[1] <= 1944.0) {
                                            if (features[2] <= 8.5) {
                                                if (features[1] <= 1390.0) {
                                                    epcpwm = 77.55555555555556;
                                                } else {
                                                    epcpwm = 70.48484848484848;
                                                }
                                            } else {
                                                epcpwm = 76.15488215488216;
                                            }
                                        } else {
                                            if (features[0] <= 71.5) {
                                                if (features[2] <= 12.5) {
                                                    epcpwm = 77.1;
                                                } else {
                                                    epcpwm = 55.0;
                                                }
                                            } else {
                                                epcpwm = 52.0;
                                            }
                                        }
                                    } else {
                                        if (features[4] <= 194.5) {
                                            if (features[1] <= 1085.0) {
                                                if (features[1] <= 1080.0) {
                                                    epcpwm = 75.03614457831326;
                                                } else {
                                                    epcpwm = 53.0;
                                                }
                                            } else {
                                                epcpwm = 77.14;
                                            }
                                        } else {
                                            if (features[1] <= 1547.0) {
                                                epcpwm = 79.0;
                                            } else {
                                                epcpwm = 52.0;
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (features[2] <= 8.5) {
                                    epcpwm = 75.28571428571429;
                                } else {
                                    epcpwm = 66.46428571428571;
                                }
                            }
                        }
                    }
                }
            } else {
                if (features[0] <= 57.5) {
                    if (features[4] <= 190.5) {
                        if (features[2] <= 47.5) {
                            if (features[4] <= 188.5) {
                                epcpwm = 71.29962264150943;
                            } else {
                                if (features[3] <= 3.5) {
                                    epcpwm = 71.6973293768546;
                                } else {
                                    epcpwm = 73.16953316953317;
                                }
                            }
                        } else {
                            if (features[0] <= 56.5) {
                                epcpwm = 73.3652034015169;
                            } else {
                                epcpwm = 74.01032702237522;
                            }
                        }
                    } else {
                        if (features[2] <= 47.5) {
                            if (features[1] <= 2361.5) {
                                if (features[4] <= 196.5) {
                                    epcpwm = 73.34235342353423;
                                } else {
                                    if (features[2] <= 45.5) {
                                        epcpwm = 73.62162162162163;
                                    } else {
                                        if (features[0] <= 54.5) {
                                            epcpwm = 73.5;
                                        } else {
                                            if (features[2] <= 46.5) {
                                                epcpwm = 53.05882352941177;
                                            } else {
                                                epcpwm = 64.36842105263158;
                                            }
                                        }
                                    }
                                }
                            } else {
                                epcpwm = 74.85054945054945;
                            }
                        } else {
                            if (features[1] <= 2427.5) {
                                if (features[1] <= 2046.5) {
                                    if (features[1] <= 1785.5) {
                                        epcpwm = 72.86486486486487;
                                    } else {
                                        epcpwm = 76.16484801247077;
                                    }
                                } else {
                                    if (features[4] <= 192.5) {
                                        if (features[0] <= 55.5) {
                                            epcpwm = 74.09270216962524;
                                        } else {
                                            epcpwm = 74.78877314814815;
                                        }
                                    } else {
                                        if (features[2] <= 53.5) {
                                            if (features[1] <= 2388.5) {
                                                if (features[2] <= 51.5) {
                                                    if (features[1] <= 2330.0) {
                                                        epcpwm = 72.784;
                                                    } else {
                                                        epcpwm = 74.33033033033033;
                                                    }
                                                } else {
                                                    epcpwm = 74.8830897703549;
                                                }
                                            } else {
                                                epcpwm = 75.83106796116505;
                                            }
                                        } else {
                                            if (features[0] <= 55.5) {
                                                if (features[1] <= 2169.5) {
                                                    epcpwm = 75.52397995705083;
                                                } else {
                                                    epcpwm = 74.88743455497382;
                                                }
                                            } else {
                                                epcpwm = 75.65573770491804;
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (features[2] <= 59.5) {
                                    epcpwm = 76.33845245126993;
                                } else {
                                    epcpwm = 72.125;
                                }
                            }
                        }
                    }
                } else {
                    if (features[2] <= 49.5) {
                        if (features[0] <= 61.5) {
                            if (features[4] <= 189.5) {
                                epcpwm = 73.35466666666666;
                            } else {
                                if (features[2] <= 39.5) {
                                    epcpwm = 74.85460599334073;
                                } else {
                                    epcpwm = 75.88064516129032;
                                }
                            }
                        } else {
                            if (features[0] <= 77.5) {
                                if (features[4] <= 183.5) {
                                    if (features[0] <= 67.5) {
                                        epcpwm = 74.01055408970976;
                                    } else {
                                        epcpwm = 76.59358288770053;
                                    }
                                } else {
                                    if (features[1] <= 2201.5) {
                                        if (features[0] <= 65.5) {
                                            if (features[4] <= 189.5) {
                                                epcpwm = 75.47128378378379;
                                            } else {
                                                if (features[2] <= 38.5) {
                                                    epcpwm = 76.2247619047619;
                                                } else {
                                                    epcpwm = 77.33535108958837;
                                                }
                                            }
                                        } else {
                                            if (features[1] <= 864.0) {
                                                epcpwm = 59.0;
                                            } else {
                                                epcpwm = 77.47112462006079;
                                            }
                                        }
                                    } else {
                                        if (features[2] <= 47.5) {
                                            if (features[4] <= 196.5) {
                                                epcpwm = 76.61304347826086;
                                            } else {
                                                if (features[0] <= 63.5) {
                                                    epcpwm = 77.52173913043478;
                                                } else {
                                                    if (features[2] <= 42.5) {
                                                        epcpwm = 54.0;
                                                    } else {
                                                        epcpwm = 70.78125;
                                                    }
                                                }
                                            }
                                        } else {
                                            if (features[0] <= 67.5) {
                                                if (features[1] <= 2286.5) {
                                                    epcpwm = 66.0;
                                                } else {
                                                    if (features[4] <= 193.5) {
                                                        epcpwm = 76.92753623188406;
                                                    } else {
                                                        if (features[2] <= 48.5) {
                                                            if (features[1] <= 2330.0) {
                                                                epcpwm = 78.6;
                                                            } else {
                                                                epcpwm = 53.857142857142854;
                                                            }
                                                        } else {
                                                            epcpwm = 76.3125;
                                                        }
                                                    }
                                                }
                                            } else {
                                                if (features[0] <= 71.0) {
                                                    epcpwm = 59.388888888888886;
                                                } else {
                                                    if (features[1] <= 2342.0) {
                                                        epcpwm = 74.33333333333333;
                                                    } else {
                                                        epcpwm = 63.0;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                if (features[1] <= 1585.0) {
                                    epcpwm = 50.0;
                                } else {
                                    if (features[0] <= 104.5) {
                                        epcpwm = 74.13414634146342;
                                    } else {
                                        if (features[1] <= 2830.5) {
                                            epcpwm = 58.42857142857143;
                                        } else {
                                            epcpwm = 75.0;
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (features[0] <= 61.5) {
                            if (features[4] <= 191.5) {
                                if (features[1] <= 2228.5) {
                                    epcpwm = 75.3697705802969;
                                } else {
                                    epcpwm = 76.08675799086758;
                                }
                            } else {
                                if (features[1] <= 2433.5) {
                                    epcpwm = 76.80278147654978;
                                } else {
                                    if (features[2] <= 62.5) {
                                        epcpwm = 77.56456456456456;
                                    } else {
                                        epcpwm = 71.41176470588235;
                                    }
                                }
                            }
                        } else {
                            if (features[1] <= 3561.0) {
                                if (features[1] <= 1196.0) {
                                    epcpwm = 65.0;
                                } else {
                                    if (features[0] <= 72.5) {
                                        if (features[4] <= 190.5) {
                                            if (features[0] <= 65.5) {
                                                epcpwm = 77.37916152897657;
                                            } else {
                                                epcpwm = 78.24214417744916;
                                            }
                                        } else {
                                            if (features[1] <= 2164.5) {
                                                epcpwm = 77.54328878558978;
                                            } else {
                                                if (features[1] <= 2233.5) {
                                                    if (features[2] <= 59.5) {
                                                        if (features[2] <= 56.5) {
                                                            epcpwm = 76.93181818181819;
                                                        } else {
                                                            if (features[1] <= 2192.5) {
                                                                epcpwm = 76.48936170212765;
                                                            } else {
                                                                epcpwm = 73.83793103448276;
                                                            }
                                                        }
                                                    } else {
                                                        epcpwm = 78.01020408163265;
                                                    }
                                                } else {
                                                    if (features[1] <= 2717.5) {
                                                        epcpwm = 77.57754010695187;
                                                    } else {
                                                        if (features[1] <= 2759.5) {
                                                            epcpwm = 60.0;
                                                        } else {
                                                            epcpwm = 76.41176470588235;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    } else {
                                        epcpwm = 74.71578947368421;
                                    }
                                }
                            } else {
                                epcpwm = 52.0;
                            }
                        }
                    }
                }
            }
        }
    }
    return epcpwm;
}
