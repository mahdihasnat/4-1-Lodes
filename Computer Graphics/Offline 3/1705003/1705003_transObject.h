#ifndef E2BF7435_307B_456A_92D5_6DA42F519279
#define E2BF7435_307B_456A_92D5_6DA42F519279

template<typename T>
class TransObject
{
public:
    virtual Vec3<T> getNormalAt(Vec3<T> const& point) = 0;
    virtual bool getRefractedRay(
        Ray<T> const &transmittedRay,
        Color<T> const&color,
        Ray<T> &reverseIncidentRay)
    {
        // see resource/reverse_incident_calculation.jpeg for derivation
        //  N is opposite direction of T
//        ~I       N
//        /\      /|\
//          \      |
//           \     |
//            \    |
//             \   |
//              \  |
//               \ |
//                \|
//                 |
// --------------------------------
//                 |\
//                 | \
//                 |  \
//                 |   \
//                 |    \
//                 |     \
//                 |      \
//                 |       \
//                 |        \
//                 |         \/
//                            T

        // ~I = N (sqrt(1-(itaTOverItaI*itaTOverItaI) * (1 - (-N dot T )^2))) 
        // 	+ ItaTOverItaI * ( - T - N ( - N dot T ));
        Vec3<T> normal = getNormalAt(transmittedRay.getOrigin());
        if(normal.dot(transmittedRay.getDirection())  >0)
        {
            normal = -normal;
        }
        // now normal is opposite direction of T
        T itaTOverItaI = getItaTOverItaI(transmittedRay.getDirection());
        T cosThetaT = -normal.dot(transmittedRay.getDirection());
        T cosThetaTSquare = cosThetaT * cosThetaT;
        T sinThetaTSquare = 1 - cosThetaTSquare;
        T temp = sinThetaTSquare * itaTOverItaI * itaTOverItaI;
        if(temp > T(1))
        {
            return false;
        }
        reverseIncidentRay.setDirection( normal * (sqrt(1 - temp))
            + ( -transmittedRay.getDirection() - normal * cosThetaT) * itaTOverItaI);
        reverseIncidentRay.setOrigin(transmittedRay.getOrigin());
        return true;
    }
    virtual T getItaTOverItaI(Vec3<T> const& transmittedRay) = 0;
};

#endif /* E2BF7435_307B_456A_92D5_6DA42F519279 */
