import matplotlib.pyplot as plt

# Datos del Clúster (96 Cores, N=10^10, Función seno)
procesos = [1, 2, 4, 8, 16, 32, 48, 64, 80, 96]
speedup_real = [1.00, 2.00, 3.85, 7.96, 14.74, 30.74, 42.49, 48.52, 64.66, 67.90]
eficiencia = [1.00, 1.00, 0.96, 1.00, 0.92, 0.96, 0.89, 0.76, 0.81, 0.71]
speedup_ideal = procesos # El ideal es Sp = p

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 5))

# --- Subplot 1: SpeedUp ---
ax1.plot(procesos, speedup_ideal, 'r--', label='SpeedUp Ideal (Lineal)')
ax1.plot(procesos, speedup_real, 'bo-', linewidth=2, markersize=6, label='SpeedUp Real (sin(x^2))')
ax1.set_title('Análisis de Escalabilidad (SpeedUp)', fontsize=14, fontweight='bold')
ax1.set_xlabel('Cantidad de Procesos', fontsize=12)
ax1.set_ylabel('SpeedUp', fontsize=12)
ax1.set_xticks(procesos)
ax1.grid(True, linestyle='--', alpha=0.7)
ax1.legend(fontsize=11)

# --- Subplot 2: Eficiencia ---
ax2.axhline(y=1.0, color='r', linestyle='--', label='Eficiencia Ideal (100%)')
ax2.plot(procesos, eficiencia, 'go-', linewidth=2, markersize=6, label='Eficiencia Real')
ax2.set_title('Eficiencia vs Cantidad de Procesos', fontsize=14, fontweight='bold')
ax2.set_xlabel('Cantidad de Procesos', fontsize=12)
ax2.set_ylabel('Eficiencia', fontsize=12)
ax2.set_xticks(procesos)
ax2.set_ylim(0.4, 1.1)
ax2.grid(True, linestyle='--', alpha=0.7)
ax2.legend(fontsize=11)

plt.tight_layout()
plt.savefig('grafico_rendimiento.png', dpi=300)
print("Gráfico 'grafico_rendimiento.png' generado con éxito.")