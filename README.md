# Complementarity-Equilibrium-Network-CordonPricing

## Cordon Pricing Implementation

The cordon pricing mechanism is implemented by adding additional costs to the arcs that cross the cordon boundary. This simulates the effect of charging for entering a congested area. The model adjusts the link cost functions to include the cordon tolls, affecting route choices and overall network equilibrium.

### Parameters

- **Cordon Toll Amount**: The additional cost when crossing the cordon.
- **Cordon Boundary Definition**: Specified in the network data by marking arcs that cross into the cordon area.
