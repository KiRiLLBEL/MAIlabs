#include <stdio.h>
#include <math.h>

const int INT_MAX = 2147483647;

int main(void) {
    char Symbol;
    long long Number = 0;
    int Sign = 0;
    int Error = 0;
    int First_world = 1;
    int First_sign = 1;
    int First_symbol = 1;
    int Start = 0;
    int Zero = 0;
    while (scanf("%c", &Symbol) != EOF) {
        switch (Symbol)
        {
        case '0': 
            Start = 1;
            if (First_symbol == 1) {
                Number = 0;
                Zero = 1;
                First_symbol = 0;
            }
            else if (Zero == 1) {
                Number = 0;
            } 
            else {
                Number = Number * 10;
            }
        break;

        case '1': 
            Start = 1;
            Zero = 0;
            if (First_symbol == 1) {
                Number = 1;
                First_symbol = 0;
            } else {
                Number = Number * 10 + 1;
            }
        break;

        case '2': 
            Start = 1;
            Zero = 0;
            if (First_symbol == 1) {
                Number = 2;
                First_symbol = 0;
            } else {
                Number = Number * 10 + 2;
            }
        break;
        
        case '3': 
            Start = 1;
            Zero = 0;
            if (First_symbol == 1) {
                Number = 3;
                First_symbol = 0;
            } else {
                Number = Number * 10 + 3;
            }
        break;

        case '4': 
            Start = 1;
            Zero = 0;
            if (First_symbol == 1) {
                Number = 4;
                First_symbol = 0;
            } else {
                Number = Number * 10 + 4;
            }
        break;
        
        case '5': 
            Start = 1;
            Zero = 0;
            if (First_symbol == 1) {
                Number = 5;
                First_symbol = 0;
            } else {
                Number = Number * 10 + 5;
            }
        break;

        case '6': 
            Start = 1;
            Zero = 0;
            if (First_symbol == 1) {
                Number = 6;
                First_symbol = 0;
            } else {
                Number = Number * 10 + 6;
            }
        break;

        case '7': 
            Start = 1;
            Zero = 0;
            if (First_symbol == 1) {
                Number = 7;
                First_symbol = 0;
            } else {
                Number = Number * 10 + 7;
            }
        break;

        case '8': 
            Start = 1;
            Zero = 0;
            if (First_symbol == 1) {
                Number = 8;
                First_symbol = 0;
            } else {
                Number = Number * 10 + 8;
            }
        break;
        
        case '9': 
            Start = 1;
            Zero = 0;
            if (First_symbol == 1) {
                Number = 9;
                First_symbol = 0;
            } else {
                Number = Number * 10 + 9;
            }
        break;

        case '+': 
            if (First_sign == 1 && First_symbol == 1) {
                Sign = 1;
                First_sign = 0;
            } else {
                Error = 1;
            }
        break;

        case '-': 
            if (First_sign == 1 && First_symbol == 1) {
                Sign = 2;
                First_sign = 0;
            } else {
                Error = 1;
            }
        break;

        case '\n': 
            if (Start == 1) {
                if (Number == 0) {
                    if (Sign == 0) {
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" %lld", Number);
                            }
                        }
                    } 
                    else if (Sign == 1) {
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("+%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" +%lld", Number);
                            }
                        }
                    } else {
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("-%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" -%lld", Number);
                            }
                        }
                    }
                } else {
                    if (Sign == 0) {
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" %lld", Number);
                            }
                        }
                    }
                    else if (Sign == 1) {
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("+%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" +%lld", Number);
                            }
                        }
                    } else {
                        Number = Number * -1;
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" %lld", Number);
                            }
                        }
                    }
                }
            }
            printf("\n");
            Number = 0;
            Sign = 0;
            Error = 0;
            First_world = 1;
            First_sign = 1;
            First_symbol = 1;
            Start = 0;
        break;

        case '\t':
            if (Start == 1) {
                if (Number == 0) {
                    if (Sign == 0) {
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" %lld", Number);
                            }
                        }
                    }
                    else if (Sign == 1) {
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("+%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" +%lld", Number);
                            }
                        }
                    } else {
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("-%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" %lld", Number);
                            }
                        }
                    }
                } else {
                    if (Sign == 0) {
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" %lld", Number);
                            }
                        }
                    } 
                    else if (Sign == 1) {
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("+%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" +%lld", Number);
                            }
                        }
                    } else {
                        Number = Number * -1;
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" %lld", Number);
                            }
                        }
                    }
                }
            }
            Number = 0;
            Sign = 0;
            Error = 0;
            First_sign = 1;
            First_symbol = 1;
            Start = 0;
        break;

        case ' ': 
            if (Start == 1) {
                if (Number == 0) {
                    if (Sign == 0) {
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" %lld", Number);
                            }
                        }
                    } 
                    else if (Sign == 1) {
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("+%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" +%lld", Number);
                            }
                        }
                    }
                    else {
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("-%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" -%lld", Number);
                            }
                        }
                    }
                } else {
                    if (Sign == 0) {
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" %lld", Number);
                            }
                        }
                    } 
                    else if (Sign == 1) {
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("+%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" +%lld", Number);
                            }
                        }
                    }
                    else {
                        Number = Number * -1;
                        if (First_world == 1) {
                            if (Number <= INT_MAX && Error == 0) {
                                printf("%lld", Number);
                                First_world = 0;
                            }
                        } else {
                            if (Number <= INT_MAX && Error == 0) {
                                printf(" %lld", Number);
                            }
                        }
                    }
                }
            }
            Number = 0;
            Sign = 0;
            Error = 0;
            First_sign = 1;
            First_symbol = 1;
            Start = 0;
        break;

        default:
            Error = 1;
        break;
        }
    }
}