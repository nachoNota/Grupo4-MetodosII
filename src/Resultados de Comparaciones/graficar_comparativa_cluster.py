import matplotlib.pyplot as plt

# Datos para la función exp(-x^2) en el Clúster HPC (N=10^10)
etiquetas_procesos = ['1 Proceso', '32 Procesos', '64 Procesos', '96 Procesos']
posiciones_x = [0, 1, 2, 3]
ancho_barra = 0.35

tiempo_valor_medio = [212.80, 7.43, 5.98, 4.17]
tiempo_muestreo_aleatorio = [409.81, 12.80, 6.66, 5.98]

fig, ax = plt.subplots(figsize=(10, 6))

# Dibujar las barras agrupadas
barras_vm = ax.bar([p - ancho_barra/2 for p in posiciones_x], tiempo_valor_medio, ancho_barra, label='Valor Medio', color='#2ca02c', edgecolor='black')
barras_ma = ax.bar([p + ancho_barra/2 for p in posiciones_x], tiempo_muestreo_aleatorio, ancho_barra, label='Muestreo Aleatorio', color='#ff7f0e', edgecolor='black')

ax.set_title('Comparativa de Rendimiento en Clúster HPC - exp(-x^2) [N = 10^{10}]', fontsize=14, fontweight='bold')
ax.set_xlabel('Cantidad de Procesos', fontsize=12)
ax.set_ylabel('Tiempo de Ejecución (segundos) - Escala Logarítmica', fontsize=12)
ax.set_xticks(posiciones_x)
ax.set_xticklabels(etiquetas_procesos, fontsize=11)
ax.set_yscale('log') # Escala logarítmica fundamental para visualizar la diferencia
ax.legend(fontsize=11)
ax.grid(axis='y', which='both', linestyle='--', alpha=0.5)

# Añadir el valor numérico encima de cada barra
for barra in barras_vm + barras_ma:
    altura = barra.get_height()
    ax.annotate(f'{altura:.2f}s',
                xy=(barra.get_x() + barra.get_width() / 2, altura),
                xytext=(0, 3), 
                textcoords="offset points",
                ha='center', va='bottom', fontsize=9, fontweight='bold')

plt.tight_layout()
plt.savefig('comparativa_cluster.png', dpi=300)
print("Gráfico 'comparativa_cluster.png' generado con éxito.")