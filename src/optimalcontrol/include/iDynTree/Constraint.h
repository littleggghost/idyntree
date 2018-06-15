/*
 * Copyright (C) 2014,2018 Fondazione Istituto Italiano di Tecnologia
 *
 * Licensed under either the GNU Lesser General Public License v3.0 :
 * https://www.gnu.org/licenses/lgpl-3.0.html
 * or the GNU Lesser General Public License v2.1 :
 * https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html
 * at your option.
 *
 * Originally developed for Prioritized Optimal Control (2014)
 * Refactored in 2018.
 * Design inspired by
 * - ACADO toolbox (http://acado.github.io)
 * - ADRL Control Toolbox (https://adrlab.bitbucket.io/ct/ct_doc/doc/html/index.html)
 */

#ifndef IDYNTREE_OPTIMALCONTROL_CONSTRAINT_H
#define IDYNTREE_OPTIMALCONTROL_CONSTRAINT_H

#include <cstddef>
#include <string>
#include <iDynTree/Core/VectorDynSize.h>

namespace iDynTree {

    class MatrixDynSize;

    namespace optimalcontrol {


        /**
         * @brief The Constraint virtual class definition
         *
         * Inherit publicly from this class to define a constraint of an optimal control problem.
        */

        /**
         * @warning This class is still in active development, and so API interface can change between iDynTree versions.
         * \ingroup iDynTreeExperimental
         */
        class Constraint {
        public:

            /**
             * @brief Constraint constructor
             *
             * Default constructor. It needs the constraint dimension and and an univocal name.
             *
             * @param[in] size Dimension of the constraint.
             * @param [in] name Univocal name of the constraint.
             */
            Constraint(size_t size, const std::string name);

            /**
             * @brief Default destructor.
             */
            virtual ~Constraint();

            /**
             * @brief Getter for the constraint size.
             * @return The dimension of the constraint.
             */
            size_t constraintSize() const;

            /**
             * @brief Getter for the constraint name.
             * @return The name of the constraint.
             */
            const std::string& name() const;

            /**
             * @brief Set the constraint lower bound.
             * @return True if successfull. A failure may be induced by a dimension mismatch.
             */
            bool setLowerBound(const VectorDynSize& lowerBound);

            /**
             * @brief Get the constraint lower bound.
             * @return True if the constraint has a lower bound. False otherwise.
             */
            bool getLowerBound(VectorDynSize& lowerBound);

            /**
             * @brief Set the constraint upper bound.
             * @return True if successfull. A failure may be induced by a dimension mismatch.
             */
            bool setUpperBound(const VectorDynSize& upperBound);

            /**
             * @brief Get the constraint upper bound.
             * @return True if the constraint has a lower bound. False otherwise.
             */
            bool getUpperBound(VectorDynSize& upperBound);

            /**
             * @brief Check if the constraint is satisfied given the specified state and control.
             * This method has a default implementation which exploits the definition of the bounds and the method evaluateConstraint.
             *
             * Unless particular implementations are needed, there is no need of overriding this method.
             * @param[in] time The time at which the constraint is evaluated.
             * @param[in] state The state at which the constraint is evaluated.
             * @param[in] control The control at which the constraint is evaluated.
             * @return True if successfull, false otherwise.
             */
            virtual bool isFeasiblePoint(double time,
                                         const VectorDynSize& state,
                                         const VectorDynSize& control);

            /**
             * @brief Evaluate the constraint.
             * This method has to be overriden when defining the constraint.
             * @param[in] time The time at which the constraint is evaluated.
             * @param[in] state The state at which the constraint is evaluated.
             * @param[in] control The control at which the constraint is evaluated
             * @param[out] constraint The constraint right hand value.
             * @return True if successfull, false otherwise.
             */
            virtual bool evaluateConstraint(double time,
                                            const VectorDynSize& state,
                                            const VectorDynSize& control,
                                            VectorDynSize& constraint) = 0;

            /**
             * @brief Evaluate the constraint jacobian with respect to the state variables
             * This methods evaluates the partial derivative of the constraint wrt to the state. By default, the implementation return false. The user needs to override this method if the constraint will be used, for example, within an optimal control problem that will be solved using an optimizer that needs this information (i.e. Ipopt).
             * @param[in] time The time at which the constraint jacobian is evaluated.
             * @param[in] state The state at which the constraint jacobian is evaluated.
             * @param[in] control The control at which the constraint jacobian is evaluated
             * @param[out] jacobian The jacobian right hand side value.
             * @return True if successful. False otherwise (or by default).
             */
            virtual bool constraintJacobianWRTState(double time,
                                                    const VectorDynSize& state,
                                                    const VectorDynSize& control,
                                                    MatrixDynSize& jacobian);

            /**
             * @brief Evaluate the constraint jacobian with respect to the control variables
             * This methods evaluates the partial derivative of the constraint wrt to the control. By default, the implementation return false. The user needs to override this method if the constraint will be used, for example, within an optimal control problem that will be solved using an optimizer that needs this information (i.e. Ipopt).
             * @param[in] time The time at which the constraint jacobian is evaluated.
             * @param[in] state The state at which the constraint jacobian is evaluated.
             * @param[in] control The control at which the constraint jacobian is evaluated
             * @param[out] jacobian The jacobian right hand side value.
             * @return True if successful. False otherwise (or by default).
             */
            virtual bool constraintJacobianWRTControl(double time,
                                                    const VectorDynSize& state,
                                                    const VectorDynSize& control,
                                                    MatrixDynSize& jacobian);

            /**
             * @brief The dimension the state vector is supposed to have.
             * Override this method to specify the dimension the state vector is supposed to have. This method is useful for the OptimalControlProblem class to allocate some buffers. By default it returns 0.
             * @return The expected dimension of the state vectors.
             */
            virtual size_t expectedStateSpaceSize() const;

            /**
             * @brief The dimension the control vector is supposed to have.
             * Override this method to specify the dimension the control vector is supposed to have. This method is useful for the OptimalControlProblem class to allocate some buffers. By default it returns 0.
             * @return The expected dimension of the control vectors.
             */
            virtual size_t expectedControlSpaceSize() const;


        private:
            size_t m_constraintSize;
            std::string m_constraintName;
            VectorDynSize m_valueBuffer;
        protected:
            /**
             * @brief The vector containing the lower bound.
             */
            VectorDynSize m_lowerBound;
            /**
             * @brief The vector containing the upper bound.
             */
            VectorDynSize m_upperBound;
            /**
             * @brief True if the constraint is lower bounded. Corresponds to the return value of getUpperBound
             */
            bool m_isLowerBounded;
            /**
             * @brief True if the constraint is upper bounded. Corresponds to the return value of getLowerBound
             */
            bool m_isUpperBounded;
        };

    }
}

#endif /* end of include guard: IDYNTREE_OPTIMALCONTROL_CONSTRAINT_H */
