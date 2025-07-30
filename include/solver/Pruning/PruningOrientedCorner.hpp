
class PruningOrientedCorner : {
    private:
        std::array<uint8_t, 2187> table_;

        std::vector<SpinId> allowedSpins_ = {
            SpinId::U, SpinId::U2, SpinId::U_PRIME,
            SpinId::D, SpinId::D2, SpinId::D_PRIME,
            SpinId::L, SpinId::L2, SpinId::L_PRIME,
            SpinId::R, SpinId::R2, SpinId::R_PRIME,
            SpinId::F, SpinId::F2, SpinId::F_PRIME,
            SpinId::B, SpinId::B2, SpinId::B_PRIME
        };

        static int encodeCornersOrientation(const std::array<uint8_t, 8>& corners_orientation);
        static std::array<uint8_t, 8> decodeCornersOrientation(int index);
        void writeToFile(const std::string& filename) const;

    public:
        void generateTable(Cube& cube);

        bool readFromFile(const std::string& filename);

};
