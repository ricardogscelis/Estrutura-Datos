from collections import defaultdict
import heapq


def procesar_tendencias(nombre_archivo):
  frecuencias = defaultdict(int)

  try:
    with open(nombre_archivo, "r", encoding="utf-8") as f:
      for linea in f:
        hashtag = linea.strip()

        if not hashtag:
          continue

        if hashtag == "TT":
          print("=== TOP 5 HASHTAGS EN TENDENCIA ===")

          heap = []
          for tag, freq in frecuencias.items():
            if len(heap) < 5:
              heapq.heappush(heap, (freq, tag))
            else:
              if freq > heap[0][0]:
                heapq.heappushpop(heap, (freq, tag))

          top_5 = sorted(heap, key=lambda x: x[0], reverse=True)

          for freq, tag in top_5:
            print(f"{tag}: {freq} menciones")
          print("===================================\n")
        else:
          frecuencias[hashtag] += 1

  except FileNotFoundError:
    print(f"No se pudo encontrar el archivo '{nombre_archivo}'.")


if __name__ == "__main__":
  procesar_tendencias("social_media.txt")