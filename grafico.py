import pandas as pd
import matplotlib.pyplot as plt

# Datos para cada valor de k
data_mult = {
    9: [0.000005],
    8: [0.000003],
    7: [0.000002],
    6: [0.000002],
    4: [0.000002],  # ---9465 y 9465
    3: [0.000001],
    2: [0.000002],  # ---94 72
}

data_euclideano = {
    9: [0.000058],
    8: [0.000058],
    7: [0.000052],
    6: [0.000049],
    4: [0.000066],
    3: [0.000052],
    2: [0.000050],
}

data_modular = {
    9: [8.391095],
    8: [0.526302],
    7: [0.046194 ],  # Segundos (número no especificado)
    6: [0.003310],
    5: [0.000231 ],
    4: [0.000067 ] ,
    3: [0.000046 ],
    2: [ 0.000066],
}

data_RSA = {
    9: [0.017700],
    8: [0.000170],
    7: [0.000098],  # Número: 4758349
    6: [0.000119],
    4: [0.000091],
    3: [0.000073],
    2: [0.000057],
}

# Función para calcular el promedio, ignorando "NO INFO"
def calculate_average(data):
    return {k: sum(v for v in values if v != "NO INFO") / len([v for v in values if v != "NO INFO"]) for k, values in data.items()}

# Calcular promedios para cada conjunto de datos
averages_mult = calculate_average(data_mult)
averages_euclideano = calculate_average(data_euclideano)
averages_modular = calculate_average(data_modular)
averages_RSA = calculate_average(data_RSA)

# Crear DataFrame para graficar
df_mult = pd.DataFrame(list(averages_mult.items()), columns=['k', 'average'])
df_euclideano = pd.DataFrame(list(averages_euclideano.items()), columns=['k', 'average'])
df_modular = pd.DataFrame(list(averages_modular.items()), columns=['k', 'average'])
df_RSA = pd.DataFrame(list(averages_RSA.items()), columns=['k', 'average'])

# Crear gráficos separados
fig, axs = plt.subplots(2, 2, figsize=(14, 10))

# Graficar "mult"
axs[0, 0].plot(df_mult['k'], df_mult['average'], marker='o', linestyle='-', color='b')
axs[0, 0].set_title('Promedio de Mult')

axs[0, 0].set_ylabel('Promedio')
axs[0, 0].grid()

# Graficar "euclideano"
axs[0, 1].plot(df_euclideano['k'], df_euclideano['average'], marker='o', linestyle='-', color='g')
axs[0, 1].set_title('Promedio de Euclideano')

axs[0, 1].set_ylabel('Promedio')
axs[0, 1].grid()

# Graficar "modular"
axs[1, 0].plot(df_modular['k'], df_modular['average'], marker='o', linestyle='-', color='r')
axs[1, 0].set_title('Promedio de Modular')

axs[1, 0].set_ylabel('Promedio')
axs[1, 0].grid()

# Graficar "RSA"
axs[1, 1].plot(df_RSA['k'], df_RSA['average'], marker='o', linestyle='-', color='purple')
axs[1, 1].set_title('Promedio de factorizacion')

axs[1, 1].set_ylabel('Promedio')
axs[1, 1].grid()

# Ajustar el espacio entre gráficos
plt.tight_layout()
plt.show()
