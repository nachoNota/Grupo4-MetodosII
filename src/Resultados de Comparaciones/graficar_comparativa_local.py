import matplotlib.pyplot as plt

# Datos para la función exp(-x^2) en entorno local (N=10^8)
etiquetas_procesos = ['1 Proceso', '4 Procesos', '8 Procesos', '16 Procesos']
posiciones_x = [0, 1, 2, 3]
ancho_barra = 0.35

tiempo_valor_medio = [1.006, 0.292, 0.164, 0.197]
tiempo_muestreo_aleatorio = [7.135, 2.033, 1.086, 0.812]

fig, ax = plt.subplots(figsize=(10, 6))

# Dibujar las barras agrupadas
barras_vm = ax.bar([p - ancho_barra/2 for p in posiciones_x], tiempo_valor_medio, ancho_barra, label='Valor Medio', color='#1f77b4', edgecolor='black')
barras_ma = ax.bar([p + ancho_barra/2 for p in posiciones_x], tiempo_muestreo_aleatorio, ancho_barra, label='Muestreo Aleatorio', color='#d62728', edgecolor='black')

ax.set_title('Comparativa de Rendimiento Local - exp(-x^2) [N = 10^8]', fontsize=14, fontweight='bold')
ax.set_xlabel('Cantidad de Procesos', fontsize=12)
ax.set_ylabel('Tiempo de Ejecución (segundos)', fontsize=12)
ax.set_xticks(posiciones_x)
ax.set_xticklabels(etiquetas_procesos, fontsize=11)
ax.legend(fontsize=11)
ax.grid(axis='y', linestyle='--', alpha=0.7)

# Añadir el valor numérico encima de cada barra para mayor claridad
for barra in barras_vm + barras_ma:
    altura = barra.get_height()
    ax.annotate(f'{altura:.3f}s',
                xy=(barra.get_x() + barra.get_width() / 2, altura),
                xytext=(0, 3),  # Desplazamiento vertical de 3 puntos
                textcoords="offset points",
                ha='center', va='bottom', fontsize=9)

plt.tight_layout()
plt.savefig('comparativa_local.png', dpi=300)
print("Gráfico 'comparativa_local.png' generado con éxito.")