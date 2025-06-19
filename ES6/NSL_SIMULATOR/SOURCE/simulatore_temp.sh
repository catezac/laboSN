#!/bin/bash
# Script per eseguire simulator.exe con temperature da 0.3 a 3.0 (passo 0.1)

TEMP_INIZIO=0.3
TEMP_FINE=3.0
PASSO=0.1

# Calcola il numero di simulazioni
N=$(echo "scale=0; ($TEMP_FINE - $TEMP_INIZIO) / $PASSO + 1" | bc)

echo "================================================"
echo "FASE 1: EQUILIBRAZIONE"
echo "================================================"
echo "Temperatura di equilibrazione: $TEMP_INIZIO"

# Crea backup del file originale
if [ ! -f "../INPUT/input.dat.backup" ]; then
    cp ../INPUT/input.dat ../INPUT/input.dat.backup
    echo "Backup del file input salvato come ../INPUT/input.dat.backup"
fi

# Imposta temperatura di equilibrazione e RESTART=0
sed -i "s/^TEMP[[:space:]]*[0-9]*\.*[0-9]*/TEMP $TEMP_INIZIO/" ../INPUT/input.dat
sed -i "s/^RESTART[[:space:]]*[0-9]*/RESTART 0/" ../INPUT/input.dat
echo "File ../INPUT/input.dat configurato per equilibrazione (T=$TEMP_INIZIO, RESTART=0)"

# Esegui simulazione di equilibrazione
echo "Inizio simulazione di equilibrazione..."
./simulator.exe

# Verifica che la configurazione finale sia stata generata
if [ -f "../OUTPUT/CONFIG/config.spin" ]; then
    # Sposta la configurazione finale nella cartella INPUT
    mv ../OUTPUT/CONFIG/config.spin ../INPUT/
    echo "Configurazione finale salvata in ../INPUT/CONFIG/config.spin"
    
    # Modifica RESTART da 0 a 1 nel file input.dat
    sed -i "s/^RESTART[[:space:]]*[0-9]*/RESTART 1/" ../INPUT/input.dat
    echo "RESTART impostato a 1 nel file ../INPUT/input.dat"
    
    echo "Equilibrazione completata con successo!"
else
    echo "ERRORE: File confing.spin non trovato dopo l'equilibrazione!"
    echo "Impossibile procedere con le simulazioni"
    exit 1
fi

echo ""
echo "================================================"
echo "FASE 2: SIMULAZIONI A TEMPERATURE MULTIPLE"
echo "================================================"
echo "Temperature: da $TEMP_INIZIO a $TEMP_FINE (passo: $PASSO)"
echo "Numero totale simulazioni: $N"
echo "================================================"

# Inizializza i file riassuntivi per tutte le righe finali complete
echo "#  ACTUAL_M:     M_AVE:       ERROR:" > ../OUTPUT/magnetization_summary.dat
echo "#  ACTUAL_M:     M_AVE:       ERROR:" > ../OUTPUT/total_energy_summary.dat
echo "#  ACTUAL_M:     M_AVE:       ERROR:" > ../OUTPUT/susceptibility_summary.dat
echo "#  ACTUAL_M:     M_AVE:       ERROR:" > ../OUTPUT/specific_heat_summary.dat
echo "File riassuntivi inizializzati per salvare righe complete: magnetization_summary.dat, total_energy_summary.dat, susceptibility_summary.dat, specific_heat_summary.dat"

# Contatore per le simulazioni
counter=1

# Loop con incremento di 0.1
TEMP=$TEMP_INIZIO
while (( $(echo "$TEMP <= $TEMP_FINE" | bc -l) )); do
    echo ""
    echo "--- Simulazione $counter/$N ---"
    echo "Temperatura: $TEMP"
    
    # Modifica il file INPUT/input.dat con la nuova temperatura
    # Mantiene la formattazione con gli spazi e RESTART=1
    sed -i "s/^TEMP[[:space:]]*[0-9]*\.*[0-9]*/TEMP $TEMP/" ../INPUT/input.dat
    echo "File ../INPUT/input.dat aggiornato con temperatura $TEMP"
    
    # Esegui il simulatore (ora legge la temperatura dal file input.dat)
    ./simulator.exe
    
    # Rinomina i file nella cartella OUTPUT del simulatore (aggiungendo la temperatura)
    # Rimuovi il punto dalla temperatura per il nome file (es: 1.2 -> 1_2)
    temp_nome=$(echo "$TEMP" | sed 's/\./_/g')
    
    # Rinomina i file specifici che genera il simulatore nella cartella OUTPUT
    if [ -f "../OUTPUT/magnetization.dat" ]; then
        mv "../OUTPUT/magnetization.dat" "../OUTPUT/magnetization_${temp_nome}.dat"
        echo "Rinominato: ../OUTPUT/magnetization_${temp_nome}.dat"
    fi
    
    if [ -f "../OUTPUT/total_energy.dat" ]; then
        mv "../OUTPUT/total_energy.dat" "../OUTPUT/total_energy_${temp_nome}.dat"
        echo "Rinominato: ../OUTPUT/total_energy_${temp_nome}.dat"
    fi
    
    if [ -f "../OUTPUT/susceptibility.dat" ]; then
        mv "../OUTPUT/susceptibility.dat" "../OUTPUT/susceptibility_${temp_nome}.dat"
        echo "Rinominato: ../OUTPUT/susceptibility_${temp_nome}.dat"
    fi
    
    if [ -f "../OUTPUT/specific_heat.dat" ]; then
        mv "../OUTPUT/specific_heat.dat" "../OUTPUT/specific_heat_${temp_nome}.dat"
        echo "Rinominato: ../OUTPUT/specific_heat_${temp_nome}.dat"
    fi
    
    echo "Simulazione $counter completata (T=$TEMP)"

    
    # Salva le ultime righe complete di tutte le quantità nei file riassuntivi
    if [ -f "../OUTPUT/magnetization_${temp_nome}.dat" ]; then
        ultima_riga=$(tail -n 1 "../OUTPUT/magnetization_${temp_nome}.dat")
        echo "$TEMP $ultima_riga" >> ../OUTPUT/magnetization_summary.dat
        #echo "Ultima riga magnetizzazione (T=$TEMP): $ultima_riga"
    fi
    
    if [ -f "../OUTPUT/total_energy_${temp_nome}.dat" ]; then
        ultima_riga=$(tail -n 1 "../OUTPUT/total_energy_${temp_nome}.dat")
        echo "$TEMP $ultima_riga" >> ../OUTPUT/total_energy_summary.dat
        echo "Ultima riga energia totale (T=$TEMP): $ultima_riga"
    fi
    
    if [ -f "../OUTPUT/susceptibility_${temp_nome}.dat" ]; then
        ultima_riga=$(tail -n 1 "../OUTPUT/susceptibility_${temp_nome}.dat")
        echo "$TEMP $ultima_riga" >> ../OUTPUT/susceptibility_summary.dat
        echo "Ultima riga suscettibilità (T=$TEMP): $ultima_riga"
    fi
    
    if [ -f "../OUTPUT/specific_heat_${temp_nome}.dat" ]; then
        ultima_riga=$(tail -n 1 "../OUTPUT/specific_heat_${temp_nome}.dat")
        echo "$TEMP $ultima_riga" >> ../OUTPUT/specific_heat_summary.dat
        echo "Ultima riga calore specifico (T=$TEMP): $ultima_riga"
    fi
    
    # Log delle esecuzioni
    echo "$(date): Simulazione $counter completata con temperatura $TEMP" >> simulazioni.log
    
    # Verifica che la configurazione finale sia stata generata
    if [ -f "../OUTPUT/CONFIG/config.spin" ]; then
        # Sposta la configurazione finale nella cartella INPUT
        mv ../OUTPUT/CONFIG/config.spin ../INPUT/
        echo "Configurazione finale salvata in ../INPUT/CONFIG/config.spin"

    else
        echo "ERRORE: File confing.spin non trovato dopo l'equilibrazione!"
        echo "Impossibile procedere con le simulazioni"
    fi

    # Incrementa temperatura e contatore
    TEMP=$(echo "scale=1; $TEMP + $PASSO" | bc)
    counter=$((counter + 1))

done

echo ""
echo "================================================"
echo "Tutte le $N simulazioni completate!"
echo "Risultati rinominati in: OUTPUT/"
echo "Backup salvato in: ../INPUT/input.dat.backup"
echo "Log salvato in: simulazioni.log"