/*

 sftools - Copyright (c) 2012-2013 Marco Antognini <antognini.marco@gmail.com>

 This software is provided 'as-is', without any express or implied warranty. In
 no event will the authors be held liable for any damages arising from the use
 of this software.

 Permission is granted to anyone to use this software for any purpose, including
 commercial applications, and to alter it and redistribute it freely, subject to
 the following restrictions:

 1. The origin of this software must not be misrepresented; you must not claim
 that you wrote the original software. If you use this software in a product,
 an acknowledgment in the product documentation would be appreciated but is
 not required.

 2. Altered source versions must be plainly marked as such, and must not be
 misrepresented as being the original software.

 3. This notice may not be removed or altered from any source distribution.

 */

/*!
 @file sftools/Curve.hpp
 @brief Define Curve drawable.
 @note Requires C++11
 */

#ifndef __SFTOOLS_CURVE_HPP__
#define __SFTOOLS_CURVE_HPP__

#include <SFML/Graphics.hpp>

namespace sftools
{
    /*!
     * Type of a curve's function
     *
     * Compute a point from one floating point paramter
     */
    typedef std::function<sf::Vector2f(float)> CurveFunction;

    /*!
     * Holds all informations used to compute the points of a curve
     *
     * The curve's points are computed with f(p) where p is in the range [begin, end].
     * PointCount defines the "resolution" or "accuracy" of the computation.
     */
    struct CurveInfo
    {
    public:
        /*!
         * Build a CurveInfo that represents an elipse
         *
         * @param a semi-major axis
         * @param b semi-minor axis
         * @param begin start angle in radian
         * @param end end angle in radian
         * @param pointCount "resolution" or "accuracy" of the computation.
         */
        static CurveInfo elipse(float a, float b, float begin, float end, unsigned int pointCount)
        {
            auto f = [a, b](float t) -> GPoint {
                return { a * std::cos(t), b * std::sin(t) };
            };

            return { f, begin, end, pointCount };
        }

        /*!
         * Build a CurveInfo that represents a circle
         *
         * @param r radius
         * @param begin start angle in radian
         * @param end end angle in radian
         * @param pointCount "resolution" or "accuracy" of the computation.
         */
        static CurveInfo circle(float r, float begin, float end, unsigned int pointCount)
        {
            return elipse(r, r, begin, end, pointCount);
        }

        /*!
         * Build a CurveInfo that represents a sine
         *
         * @param a x-axis factor
         * @param b y-axis factor
         * @param begin start angle in radian
         * @param end end angle in radian
         * @param pointCount "resolution" or "accuracy" of the computation.
         */
        static CurveInfo sine(float a, float b, float begin, float end, unsigned int pointCount)
        {
            auto f = [a, b](float t) -> GPoint {
                return { a * t, b * std::sin(t) };
            };

            return { f, begin, end, pointCount };
        }

        /*!
         * Build a CurveInfo that represents a cosine
         *
         * @param a x-axis factor
         * @param b y-axis factor
         * @param begin start angle in radian
         * @param end end angle in radian
         * @param pointCount "resolution" or "accuracy" of the computation.
         */
        static CurveInfo cosine(float a, float b, float begin, float end, unsigned int pointCount)
        {
            auto f = [a, b](float t) -> GPoint {
                return { a * t, b * std::cos(t) };
            };

            return { f, begin, end, pointCount };
        }
        
    public:
        CurveFunction f; ///< Curve's function
        float begin; ///< First value of the curve's parameter
        float end; ///< Last value of the curve's parameter
        unsigned int pointCount; ///< "Resolution" of the curve
    };

    /*!
     * Drawable representing a mathematical curve.
     *
     * You can draw partial circle, ellipse, sine, etc... curves with this class.
     */
    class Curve : public sf::Drawable,
                  public sf::Transformable
    {
    public:
        /*!
         * Construct a curve
         *
         * @param info curve's info
         * @param color curve's color
         * @param thickness curve's thickness
         */
        Curve(CurveInfo info, sf::Color color = sf::Color::Black, float thickness = 1.f)
        : m_vertices(sf::PrimitiveType::TrianglesStrip)
        , m_info(info)
        , m_color(color)
        , m_thickness(thickness)
        {
            update();
        }

        /*!
         * Virtual destructor
         */
        virtual ~Curve()
        {
            // Nothing to do here.
        }
        
        /*!
         * Get the local bounding rectangle of the entity
         *
         * The returned rectangle is in local coordinates, which means
         * that it ignores the transformations (translation, rotation,
         * scale, ...) that are applied to the entity.
         * In other words, this function returns the bounds of the
         * entity in the entity's coordinate system.
         *
         * @return Local bounding rectangle of the entity
         */
        sf::FloatRect getLocalBounds() const
        {
            return m_vertices.getBounds();
        }

        /*!
         * Get the global bounding rectangle of the entity
         *
         * The returned rectangle is in global coordinates, which means
         * that it takes in account the transformations (translation,
         * rotation, scale, ...) that are applied to the entity.
         * In other words, this function returns the bounds of the
         * sprite in the global 2D world's coordinate system.
         *
         * @return Global bounding rectangle of the entity
         */
        sf::FloatRect getGlobalBounds() const
        {
            return getTransform().transformRect(getLocalBounds());
        }

        /*!
         * Get the curve's info
         *
         * @return the curve's info
         */
        CurveInfo const& getInfo() const
        {
            return m_info;
        }

        /*!
         * Set the curve's info
         *
         * @return info new curve's info
         */
        void setInfo(CurveInfo const& info)
        {
            m_info = info;
            update();
        }

        /*!
         * Get the curve's color
         *
         * @return curve's color
         */
        sf::Color getColor() const
        {
            return m_color;
        }

        /*!
         * Set the curve's color
         *
         * @param color new curve's color
         */
        void setColor(sf::Color color)
        {
            m_color = color;
            updateColorOnly();
        }

        /*!
         * Get the curve's thickness
         *
         * @return curve's thickness
         */
        float getThickness() const
        {
            return m_thickness;
        }

        /*!
         * Set the curve's thickness
         *
         * @param thickness new curve's thickness
         */
        void setThickness(float thickness)
        {
            m_thickness = thickness;
            update();
        }

    protected:
        /*!
         * Draw the curve to a render target
         *
         * @param target Render target to draw to
         * @param states Current render states
         */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        /*!
         * Update vertices cache.
         */
        void update()
        {
            // Compute the normalised normal of [a, b] segment.
            // Note: we do it here just to reduce a little bit the inter-dependencies.
            auto const normalisedNormal = [](sf::Vector2f const& a, sf::Vector2f const& b) -> sf::Vector2f
            {
                sf::Vector2f const v = a - b;
                sf::Vector2f const n = { v.y, -v.x };
                float const length = std::sqrt(n.x * n.x + n.y * n.y);
                
                return length != 0.0 ? n / length : n;
            };

            m_vertices.clear();
            m_vertices.resize(m_info.pointCount * 2 - 1); // Count points for the curve and (count - 1) points for the outline
            // (that is, one point for the outline between each point of the curve)

            // Compute the points of the curve
            float const step = (m_info.end - m_info.begin) / m_info.pointCount;
            for (unsigned int i = 0; i < m_info.pointCount; ++i) {
                float const t = m_info.begin + step * i;
                m_vertices[i * 2] = { m_info.f(t), m_color }; // one vertex over two because of the outline
            }

            // Compute the points of the outline
            for (unsigned int i = 1; i < m_info.pointCount * 2 - 1; i += 2) {
                // Compute the normal of the two points (p0 and p2) of the curve that are next to this outline point (p1)
                GPoint const& p0 = m_vertices[i - 1].position;
                GPoint const& p2 = m_vertices[i + 1].position;
                GPoint const  n  = normalisedNormal(p0, p2);
                GPoint const  m  = (p0 + p2) / 2.f;
                GPoint const  p1 = m + n * m_thickness;
                
                m_vertices[i] = { p1, m_color };
            }
        }

        /*!
         * Update vertices' color only
         *
         * No need to recompute every points.
         */
        void updateColorOnly()
        {
            for (unsigned int i = 0; i < m_vertices.getVertexCount(); ++i) {
                m_vertices[i].color = m_color;
            }
        }

    private:
        sf::VertexArray m_vertices; ///< curve's cache
        CurveInfo m_info; ///< curve's info
        sf::Color m_color; ///< curve's color
        float m_thickness; ///< curve's thickness
    };
}

#endif // __SFTOOLS_CURVE_HPP__
