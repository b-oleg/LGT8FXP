# Карта регистров

## Extended I/O Registers

| Addr | Name    | BIT7   | BIT6   | BIT5   | BIT4   | BIT3   | BIT2   | BIT1   | BIT0   |
|------|---------|--------|--------|--------|--------|--------|--------|--------|--------|
| $F6  | GUID3   | Byte 3 |
| $F5  | GUID2   | Byte 2 |
| $F4  | GUID1   | Byte 1 |
| $F3  | GUID0   | Byte 0 |
| $F2  | PMCR    | PMCE   | CLKFS  | CLKSS  | WCLKS  | OSCKEN | OSCMEN | RCKEN  | RCHEN  |
| $F0  | PMX2    | WCE    | STOSC1 | STOSC0 | -      | -      | XIEN   | E6EN   | C6EN   |
| $EE  | PMXO    | PMXCE  | C1BF4  | C1AF5  | COBFF3 | COA00  | SSB1   | TXD6   | RXD5   |
| $ED  | PMXL    | -      | -      | -      | -      | -      | C3AC   | C2BF7  | C2AF6  |
| $EC  | TCKSR   | -      | F2XEN  | TC2XF1 | TC2XF0 | -      | AFOKS  | TC2XS1 | TC2XS0 |
| $E2  | PSSR    | PSS1   | PSS3   | -      | -      | -      | -      | PSR3   | PSR1   |
| $E1  | OCPUE   | PUE7   | PUE6   | PUE5   | PUE4   | PUE3   | PUE2   | PUE1   | PUE0   |
| $E0  | HDR     | -      | -      | HDR5   | HDR4   | HDR3   | HDR2   | HDR1   | HDR0   |
| $DE  | DAPTE   | DAPTE  | -      | -      | -      | -      | -      | -      | -      |
| $DD  | DAPTR   | DAPTP  | DAP Trimming |
| $DC  | DAPCR   | DAPEN  | GA1    | GA0    | DNS2   | DNS1   | DNS0   | DPS1   | DPS0   |
| $CF  | LDOCR   | WCE    |        |        |        | PDEN   | VSEL2  | VSEL1  | VSEL0  |
| $CE  | VCAL2   |
| $CD  | VCAL1   |
| $CC  | VCAL3   |
| $C8  | VCAL    |
| $C6  | UDR     |
| $C5  | UBRRH   |
| $C4  | UBRRL   |
| $C2  | UCSRC   | UMSEL1 | UMSEL0 | UPM1   | UPM0   | USBS0  | UCSZ01 | UCSZ00 | UCPOL0 |
| $C1  | UCSRB   | RXCIE0 | TXCIE0 | UDRIE0 | RXEN0  | TXEN0  | UCSZ02 | RXB80  | TXB80  |
| $C0  | UCSRA   | RXC0   | TXC0   | UDRE0  | FE0    | DOR0   | UPE0   | U2X0   | MPCM0  |
| $BD  | TWAMR   |
| $BC  | TWCR    | TWINT  | TWEA   | TWSTA  | TWSTO  | TWWC   | TWEN   | -      | TWIE   |
| $BB  | TWDR    | 
| $BA  | TWAR    | 
| $B9  | TWSR    |        |        |        |        |        |        | TWPS   |        |
| $B8  | TWBR    |        |        |        |        |        |        |        |        |
| $B6  | ASSR    | INTCK  | -      | AS2    | TCNZB  | OCR2AUB| OCR2BUB| TCR2AUB| TCR2BUB|
| $B4  | OCR2B   | 
| $B3  | OCR2A   | 
| $B2  | TCNT2   | 
| $B1  | TCCR2B  | FOC2A  | FOC2B  | -      | -      | WGM22  | CS2    |        |        |
| $B0  | TCCR2A  | COM2A1 | COM2A0 | COM2B1 | COM2B0 | -      | -      | WGM21  | WGM20  |
| $AF  | DPS2R   | -      | -      | -      | -      | DPS2E  | LPRCE  | TOS1   | TOS0   |
| $AE  | IOCWK   | IOCD7  | IOCD6  | IOCD5  | IOCD4  | IOCD3  | IOCD2  | IOCD1  | IOCD0  |
| $AD  | ADCSRD  | BGEN   | REFS2  | IVSE1L | IVSE1L0| -      | VDS2   | VDS1   | VDS0   |
| $AC  | ADMSC   | AMOF   | -      | -      | -      | AMFC3  | AMFC2  | AMFC1  | AMFC0  |
| $AB  | ADT1H   |
| $AA  | ADT1L   |
| $A9  | PORTE   |
| $A8  | DORE    |
| $A7  | PINE    |
| $A6  | ADTOH   |
| $A5  | ADTOL   |
| $A4  | OFR1    |
| $A3  | OFRO    |
| $A1  | DALR    |
| $A0  | DACON   | -      | -      | -      | -     | DACEN   | DAOE   | DAVS1  | DAVS0  |
| $9F  | OCR3CH  |
| $9E  | OCR3CL  |
| $9D  | DIR3H   |
| $9C  | DIR3L   |
| $9B  | OCR3BH  | 
| $9A  | OCR3BL  | 
| $99  | OCR3AH  | 
| $98  | OCR3AL  | 
| $97  | ICR3H   | 
| $96  | ICR3L   | 
| $95  | TCNT3H  | 
| $94  | TCNT3L  | 
| $93  | TCCR3D  | 
| $92  | TCCR3C  | 
| $91  | TCCR3B  | 
| $90  | TCCR3A  | 
| $8D  | DIR1H   | 
| $8C  | DIR1L   | 
| $8B  | OCR1BH  | 
| $8A  | OCR1BL  | 
| $89  | OCR1AH  | 
| $88  | OCR1AL  | 
| $87  | ICR1H   | 
| $86  | ICR1L   | 
| $85  | TCNT1H  | 
| $84  | TCNT1L  | 
| $83  | TCCR1D  | DSX17   | DSX16   | DSX15   | DAX14   | -       | -       | DSX11   | DSX10   |
| $82  | TCCR1C  | FOC1A   | FOC1B   | DOC1B   | DOC1A   | DTEN1   | -       | -       | -       |
| $81  | TCCR1B  | IC1C1   | IC1S1   | -       | WGM13   | WGM12   | CS1     |         |         |
| $80  | TCCR1A  | COM1A1  | COM1A0  | COM1B1  | COM1B0  | -       | -       | WGM11   | WGM10   |
| $7F  | DIR1    | PE7D    | PE6D    | PE0D    | COP0    | PC0D    | PC7D    | PD7D    | PD6D    |
| $7E  | DIR0    | PE3D    | PE1D    | PC5D    | PC4D    | PC3D    | PC2D    | PC1D    | PC0D    |
| $7D  | ADCSRC  | OFEN    | -       | SPN     | AMEN    | -       | SPD     | DIFS    | ADTM    |
| $7C  | ADMUX   | REFS1   | REFS0   | ADLAR   |                   | CHMUX   |         |         |
| $7B  | ADCSRB  | CME01   | CME00   | CME11   | CME10   | -       |         | ADTS    |         |
| $7A  | ADCSRA  | ADEN    | ADSC    | ADATE   | ADIF    | ADIE    |         | ADPS    |         |
| $79  | ADCH    | 
| $78  | ADCL    | 
| $76  | DIDR2   | -       | PBSD    | -       | -       | -       | -       | -       | -       |
| $75  | IVBASE  | 
| $74  | PCMSK4  | PCINT39 | PCINT38 | PCINT37 | PCINT36 | PCINT35 | PCINT34 | PCINT33 | PCINT32 |
| $73  | PCMSK3  | PCINT31 | PCINT30 | PCINT29 | PCINT28 | PCINT27 | PCINT36 | PCINT25 | PCINT24 |
| $71  | TIMSK3  | -       | -       | ICIE3   | -       | OCIE3C  | OCIE3B  | OCIE3A  | TOIE3   |
| $70  | TIMSK2  | -       | -       | -       | -       | -       | OCIE2B  | OCIE2A  | TOIE2   |
| $6F  | TIMSK1  | -       | -       | ICIE1   | -       | -       | OCIE1B  | OCIE1A  | TOIE1   |
| $6E  | TIMSK0  | -       | -       | -       | -       | -       | OCIE0B  | OCIE0A  | TOIE0   |
| $6D  | PCMSK2  | PCINT23 | PCINT22 | PCINT21 | PCINT20 | PCINT19 | PCINT18 | PCINT17 | PCINT16 |
| $6C  | PCMSK1  | PCINT15 | PCINT14 | PCINT13 | PCINT12 | PCINT11 | PCINT10 | PCINT9  | PCINT8  |
| $6B  | PCMSK0  | PCINT7  | PCINT6  | PCINT5  | PCINT4  | PCINT3  | PCINT2  | PCINT1  | PCINT0  |
| $69  | EICRA   | -       | -       | -       | -       | ISC11   | ISC10   | ISC01   | ISC00   |
| $68  | PCICR   | -       | -       | -       | PCIE4   | PCIE3   | PCIE2   | PCIE1   | PCIE0   |
| $67  | RCCAL   |
| $66  | RCMCAL  |
| $65  | PRR1    | -       | -       | PRWDT   | -       | PRTIM3  | PREFL   | PRPQI   | -       |
| $64  | PRR0    | PRTWI   | PRTIM2  | PRTIM0  | -       | PRTIM1  | PRSPI   | PRUSART0| PRADC   |
| $62  | VDTCR   | WCE     | SWR     | -       | VDT5    | -       | VDREN   | VDTEN   |         |
| $61  | CLKPR   | WCE     | CKDE1   | CKDE0   | -       |         | CLKPS   |         |         |
| $60  | WDTCSR  | WDIF    | WDIE    | WDP3    | WDCE    | WDE     | WDP2    | WDP1    | WDP0    |

## DirectIO Registers

| Addr | Name    | BIT7   | BIT6   | BIT5   | BIT4   | BIT3   | BIT2   | BIT1   | BIT0   |
|------|---------|--------|--------|--------|--------|--------|--------|--------|--------|
| $5F  | SREG    | I      | T      | H      | S      | V      | N      | Z      | C      |
| $5E  | SPH     | 
| $5D  | SPL     | 
| $5C  | E2PD3   | 
| $5B  | CLTR    | 
| $5A  | E2PD1   | 
| $59  | DSAH    | 
| $58  | DSAL    | 
| $57  | E2PD2   | 
| $56  | ECCR    | WEN    | EEN    | ERN    | SWM    | CP1      | CP0      | ECS1     | ECS0     |
| $55  | MCUCR   | FWKEN  | FPDEN  | SWR    | PUD    | IRLD     | IFAIL    | IVSEL    | WCE      |
| $54  | MCUSR   | SWDD   | -      | -      | OCDRF  | WDDRF    | BORF     | EXTRF    | PORF     |
| $53  | SMCR    | -      | -      | -      | -      | -        |          | SM       | SE       |
| $52  | COTR    |
| $51  | COXCR   | -      | COOE   | COHYSE | COPS0  | COWKE    | COFEN    | COFS1    | COFS0    |
| $50  | COSR    | COD    | COBG   | COO    | COI    | COIE     | COIC     | COIS     |          |
| $4F  | DTR0    |
| $4E  | SPDR    |
| $4D  | SPSR    | SPIF   | WCOL   | -      | -      | -        | DUAL     | -        | SPI2X    |
| $4C  | SPCR    | SPIE   | SPE    | DORD   | MSTR   | CPOL     | CPHA     |          | SPR      |
| $4B  | GPIOR2  |
| $4A  | GPIOR1  |
| $49  | TCCR0X  | DSX07  | DSX06  | DSX05  | DSX04  | -        | -        | DSX01    | DSX00    |
| $48  | OCR0B   |
| $47  | OCR0A   |
| $46  | TCNT0   |
| $45  | TCCR0B  | FOC0A  | FOC0B  | OCOAS  | DTEN0  | WGM02    | CS02     | CS01     | CS00     |
| $44  | TCCR0A  | COM0A1 | COM0A0 | COM0B1 | COM0B0 | DOCOB    | DOCOA    | WGM01    | WGM00    |
| $43  | GTCCR   | TSM    | -      | -      | -      | -        | -        | PSRASY   | PSRSYNC  |
| $42  | EEARH   |
| $41  | EEARL   |
| $40  | E2PD0   |
| $3F  | EECR    | EEPM2  | EEPM1  | EEPM0  | EERIE  | EEMWE    | EEWE     | EERE     |          |
| $3E  | GPIOR0  |
| $3D  | EIMSK   | -      | -      | -      | -      | -        | -        | INT1     | INT0     |
| $3C  | EIFR    | -      | -      | -      | -      | -        | -        | INTF1    | INTF0    |
| $3B  | PCIFR   | -      | -      | -      | -      | PCIF3    | PCIF2    | PCIF1    | PCIF0    |
| $3A  | CLKCR   | -      | C10E   | CLHYSE | CLPS0  | CLWKE    | CLFEN    | CLFS1    | CLFS0    |
| $39  | SPIFR   | RDFULL | RDEMPT | RDPTR1 | RDPTR0 | WRFULL   | WREMPT   | WRPTR1   | WRPTR0   |
| $38  | TIFR3   | -      | -      | ICF3   | -      | -        | OCF3B    | OCF3A    | TOV3     |
| $37  | TIFR2   | -      | -      | -      | -      | -        | OCF2B    | OCF2A    | TOV2     |
| $36  | TIFR1   | -      | -      | ICF1   | -      | -        | OCF1B    | OCF1A    | TOV1     |
| $35  | TIFR0   | -      | -      | -      | -      | -        | OCF0B    | OCF0A    | TOV0     |
| $34  | PORTF   |
| $33  | DDRF    |
| $32  | PINF    |
| $31  | DSDOV   |
| $30  | DSDUX   |
| $2F  | CLKSR   | C1D    | C1BG   | C1O    | C1I    | C1IE     | C1K      | C1S      |          |
| $2E  | PORTE   |
| $2D  | DDRE    |
| $2C  | PINE    |
| $2B  | PORTD   |
| $2A  | DDRD    |
| $29  | PIND    |
| $28  | PORTC   |
| $27  | DDRC    |
| $26  | PINC    |
| $25  | PORTB   |
| $24  | DDRB    |
| $23  | PINB    |
| $22  | DSSD    |
| $21  | DSIR    |
| $20  | DSCR    | DSUEN | MM | D1 | D0 | - | DSN | DSZ | DSC |