## Exercice 2 - Lecture de code et compréhension

### Questions :

1. Identifiez où sont définies les structures principales du graphe (WeightedGraph / PositionedGraph) et expliquez brièvement leur rôle et comment elles sont utilisées.

2. Expliquez en quelques lignes le rôle des modules:
   - extraction OSM,
   - simplification,
   - visualisation.

3. Expliquez ce que vous comprenez des différentes étapes de simplification implémentées (fichier src/simplification/simplify.cpp) et les raisons pour lesquelles elles sont utilisées (leur impact sur la structure du graphe, les avantages/inconvénients, etc.).

### Réponses :

1. Les structures principales du graphe sont définies dans les fichiers `src/dataStructure/weightedGraph.cpp` et `src/osm/positionedGraph.cpp`.
   - `WeightedGraph` est une structure qui représente un graphe pondéré générique (orienté ou non orienté) sous forme de liste d'adjacence
     - `adjacency_list` : Une std::unordered_map<IDType, std::vector<WeightedArc>> qui associe chaque nœud (identifié par un IDType) à une liste de ses arcs sortants (WeightedArc)

     - `WeightedArc` : Une structure qui stocke :
       - `to` : L'ID du nœud de destination
       - `weight` : Le poids de l'arc (par défaut = 10)

   - `PositionedGraph` est une structure qui étend `WeightedGraph` en y ajoutant des positions géométriques pour chaque nœud, ce qui permet de représenter un graphe spatial (ex : carte routière, réseau de points d'intérêt)
     - `nodes` : Une std::unordered_map<OSM::NodeId, glm::vec2> qui associe chaque nœud (identifié par un OSM::NodeId) à une position 2D (glm::vec2)
     - `graph` : Une instance de DataStructure::WeightedGraph pour stocker la topologie (arcs et poids)

2. Les modules ont les rôles suivants :
   - Extraction OSM : Charge un fichier OSM, filtre les données (bâtiments, voies ferrées) et construit un graphe positionné (PositionedGraph) avec nœuds et arcs
   - Simplification : Réduit la complexité du graphe en supprimant en passant par plusieurs étapes (ex : suppression des nœuds isolés, simplification des segments, etc...) pour faciliter l'analyse et la visualisation
   - Visualisation : Affiche le graphe avec Raylib, permet de naviguer (zoom/déplacement), sélectionner des nœuds et calculer des chemins (Dijkstra)

3. Les différentes étapes de simplification implémentées dans `src/commands/simplify.cpp` comprennent :
   | Étape | Description | Impact sur le graphe | Avantages | Inconvénients |
   | ------------------------------------------------------- | ----------------------------------------------------------- | -------------------------------------------------------- | ------------------------------------------------------------- | ---------------------------------------------------------------------- |
   | keep_only_largest_connected_component | Garde uniquement la partie la plus étendue du graphe | Supprime les zones isolées | Moins de bruit, analyse plus simple | Risque de perdre des informations utiles dans les petites zones |
   | remove_small_ending_edge | Élimine les nœuds terminaux reliés par des arcs très courts | Réduit les impasses | Moins de nœuds inutiles, structure plus propre | Peut effacer des détails importants (ex : accès à des bâtiments) |
   | remove_degree_two_nodes_by_angle_threshold (1ère passe) | Remplace les nœuds de degré 2 alignés par un arc direct | Simplifie les segments droits | Réduction importante du nombre de nœuds, calculs plus rapides | Perte de précision pour les courbes légères |
   | group_nodes_by_connection_depth_and_proximity | Fusionne les nœuds proches et liés dans un rayon donné | Réduit la complexité dans les zones denses | Moins de nœuds, connectivité préservée | Perte de détails (ex : sens de circulation), risque d’arcs artificiels |
   | remove_degree_two_nodes_by_angle_threshold (2ème passe) | Applique à nouveau le lissage après les fusions | Nettoie les nœuds redondants créés par les regroupements | Résultat plus épuré | Risque de trop simplifier si les seuils sont trop stricts |
