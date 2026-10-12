import matplotlib.pyplot as plt

# Datos de Nacho: Error Relativo para exp(-x^2) con 1 y 4 procesos
N = [10**3, 10**4, 10**5, 10**6, 10**7, 10**8]
error_1_proc = [1.995434, 0.024310, 0.041700, 0.012846, 0.000301, 0.000223]
error_4_proc = [0.082956, 0.614009, 0.144734, 0.012407, 0.003135, 0.002431]

plt.figure(figsize=(9, 6))

plt.plot(N, error_1_proc, 'bo-', linewidth=2, markersize=6, label='1 Proceso')
plt.plot(N, error_4_proc, 'rs-', linewidth=2, markersize=6, label='4 Procesos')

plt.xscale('log')
plt.yscale('log') # Escala logarítmica en ambos ejes para ver mejor la caída

plt.title('Error Relativo vs Cantidad de Simulaciones (N)', fontsize=14, fontweight='bold')
plt.xlabel('N (Escala Logarítmica)', fontsize=12)
plt.ylabel('Error Relativo (%) (Escala Logarítmica)', fontsize=12)
plt.grid(True, which="both", linestyle='--', alpha=0.5)
plt.legend(fontsize=11)

plt.tight_layout()
plt.savefig('grafico_error.png', dpi=300)
print("Gráfico 'grafico_error.png' generado con éxito.")