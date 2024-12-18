#include <lead/common.h>
#include <lead/sampler.h>
#include <lead/render.h>
#include <pcg32.h>

class Independent: public Sampler {
public:
    Independent() {}
    
    Independent(const PropertyList &propList) {
        m_sampleCount = propList.getInt("sampleCount", 1);
    }

    void prepare(const Block &block) {
        m_random.seed(
            block.blockOffsetX,
            block.blockOffsetY
        );
    }

    std::unique_ptr<Sampler> clone() const {
        std::unique_ptr<Independent> cloned(new Independent());
        cloned->m_sampleCount = m_sampleCount;
        cloned->m_random = m_random;
        return std::move(cloned);
    }

    void generate() {}
    void advance() {}

    float next1D() {
        return m_random.nextFloat();
    }

    Point2f next2D() {
        return Point2f(
            m_random.nextFloat(),
            m_random.nextFloat()
        );
    }

    Point3f next3D() {
        return Point3f(
            m_random.nextFloat(),
            m_random.nextFloat(),
            m_random.nextFloat()
        );
    }

    virtual std::string toString() const {
        return "Independent[]";
    }

protected:
    pcg32 m_random;
};

LEAD_REGISTER_CLASS(Independent, "independent")