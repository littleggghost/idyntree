/*
 * Copyright (C) 2017 Fondazione Istituto Italiano di Tecnologia
 * Authors: Silvio Traversaro
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#ifndef IDYNTREE_IKIN_CONVERSIONS_H
#define IDYNTREE_IKIN_CONVERSIONS_H

#include <string>

#include <iCub/iKin/iKinFwd.h>

namespace iDynTree

{

class Model;
class DHChain;

/**
 *
 * Load a iDynTree::DHChain object from a iCub::iKin::iKinChain .
 *
 * @return true if all went ok, false otherwise.
 */
bool DHChainFromiKinChain(iCub::iKin::iKinChain & ikinChain,
                          DHChain & out);

/**
 *
 * Load a iDynTree::Model object from a iCub::iKin::iKinChain .
 *
 * @return true if all went ok, false otherwise.
 */
bool modelFromiKinChain(iCub::iKin::iKinChain & ikinChain,
                        Model & output);

/**
 * iKinLimb class to extract a iKinLimb from iDynTree structures.
 */
class iKinLimbImported : public iCub::iKin::iKinLimb
{
public:
    /**
     * Default constructor.
     */
    iKinLimbImported();

    /**
     * Default destructor.
     */
    virtual ~iKinLimbImported();

    /**
     * Initialize the limb properties from a chain in a iDynTree::Model
     */
    bool fromModel(const Model & model,
                   const std::string& baseFrame,
                   const std::string& distalFrame);

    /**
     * Initialize the limb properties from a iDynTree::DHChain
     */
    bool fromDHChain(const DHChain & dhChain);
};

/**
 *
 * Extract an iCub::iKin::iKinLimb from an iDynTree::Model .
 *
 * @return true if all went ok, false otherwise.
 */
bool iKinLimbFromModel(const Model & model,
                        const std::string& baseFrame,
                        const std::string& distalFrame,
                        iCub::iKin::iKinLimb & ikinLimb);

/**
 *
 * Create a iCub::iKin::iKinLimb from an iDynTree::DHChain
 */
bool iKinLimbFromDHChain(const DHChain & dhChain,
                         iCub::iKin::iKinLimb& ikinLimb);

}

#endif