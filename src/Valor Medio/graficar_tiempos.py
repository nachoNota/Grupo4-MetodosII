import matplotlib.pyplot as plt

# Datos Clúster 96 Cores: Tiempos de la función seno para distintas cargas
procesos = [1, 2, 4, 8, 16, 32, 48, 64, 80, 96]
tiempo_10_8 = [4.141, 2.096, 1.058, 0.541, 0.275, 0.143, 0.095, 0.077, 0.067, 0.059]
tiempo_10_9 = [41.319, 20.737, 10.493, 5.187, 2.697, 1.446, 0.961, 0.766, 0.634, 0.583]

plt.figure(figsize=(9, 6))

plt.plot(procesos, tiempo_10_8, 'mo-', linewidth=2, markersize=6, label='N = 10^8')
plt.plot(procesos, tiempo_10_9, 'co-', linewidth=2, markersize=6, label='N = 10^9')

plt.title('Tiempo de Ejecución vs Cantidad de Procesos', fontsize=14, fontweight='bold')
plt.xlabel('Cantidad de Procesos', fontsize=12)
plt.ylabel('Tiempo de Ejecución (segundos)', fontsize=12)
plt.yscale('log') # Escala logarítmica en Y porque los tiempos bajan muy rápido
plt.xticks(procesos)
plt.grid(True, which="both", linestyle='--', alpha=0.5)
plt.legend(fontsize=11)

plt.tight_layout()
plt.savefig('grafico_tiempos.png', dpi=300)
print("Gráfico 'grafico_tiempos.png' generado con éxito.")