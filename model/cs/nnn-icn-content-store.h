/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright (c) 2015 Jairo Eduardo Lopez
 *
 *   This file is part of nnnsim.
 *
 *  nnn-icn-content-store.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-icn-content-store.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with nnn-icn-content-store.h. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 */

#ifndef NNN_ICN_CONTENT_STORE_H
#define	NNN_ICN_CONTENT_STORE_H

#include <ns3-dev/ns3/object.h>
#include <ns3-dev/ns3/ptr.h>
#include <ns3-dev/ns3/traced-callback.h>

#include <boost/tuple/tuple.hpp>

namespace ns3 {

  class Packet;

  namespace icn
  {
    class Name;
  }

  namespace nnn {

    class Data;
    class Interest;

    class ContentStore;

    /**
     * @ingroup nnn
     * @defgroup nnn-cs Content Store
     */

    /**
     * @ingroup nnn-cs
     * @brief Namespace for ContentStore operations
     */
    namespace cs {

      /**
       * @ingroup nnn-cs
       * @brief NDN content store entry
       */
      class Entry : public SimpleRefCount<Entry>
      {
      public:
	/**
	 * \brief Construct content store entry
	 *
	 * \param header Parsed Data header
	 * \param packet Original Ndn packet
	 *
	 * The constructor will make a copy of the supplied packet and calls
	 * RemoveHeader and RemoveTail on the copy.
	 */
	Entry (Ptr<ContentStore> cs, Ptr<const Data> data);

	/**
	 * \brief Get prefix of the stored entry
	 * \returns prefix of the stored entry
	 */
	const icn::Name&
	GetName () const;

	/**
	 * \brief Get Data of the stored entry
	 * \returns Data of the stored entry
	 */
	Ptr<const Data>
	GetData () const;

	/**
	 * @brief Get pointer to access store, to which this entry is added
	 */
	Ptr<ContentStore>
	GetContentStore ();

      private:
	Ptr<ContentStore> m_cs; ///< \brief content store to which entry is added
	Ptr<const Data> m_data; ///< \brief non-modifiable Data
      };

    } // namespace cs

    /**
     * @ingroup nnn-cs
     * \brief Base class for NDN content store
     *
     * Particular implementations should implement Lookup, Add, and Print methods
     */
    class ContentStore : public Object
    {
    public:
      /**
       * \brief Interface ID
       *
       * \return interface ID
       */
      static
      TypeId GetTypeId ();

      /**
       * @brief Virtual destructor
       */
      virtual
      ~ContentStore ();

      /**
       * \brief Find corresponding CS entry for the given interest
       *
       * \param interest Interest for which matching content store entry
       * will be searched
       *
       * If an entry is found, it is promoted to the top of most recent
       * used entries index, \see m_contentStore
       */
      virtual Ptr<Data>
      Lookup (Ptr<const Interest> interest) = 0;

      /**
       * \brief Add a new content to the content store.
       *
       * \param header Fully parsed Data
       * \param packet Fully formed Ndn packet to add to content store
       * (will be copied and stripped down of headers)
       * @returns true if an existing entry was updated, false otherwise
       */
      virtual bool
      Add (Ptr<const Data> data) = 0;

      // /*
      //  * \brief Add a new content to the content store.
      //  *
      //  * \param header Interest header for which an entry should be removed
      //  * @returns true if an existing entry was removed, false otherwise
      //  */
      // virtual bool
      // Remove (Ptr<Interest> header) = 0;

      /**
       * \brief Print out content store entries
       */
      virtual void
      Print (std::ostream &os) const = 0;


      /**
       * @brief Get number of entries in content store
       */
      virtual uint32_t
      GetSize () const = 0;

      /**
       * @brief Return first element of content store (no order guaranteed)
       */
      virtual Ptr<cs::Entry>
      Begin () = 0;

      /**
       * @brief Return item next after last (no order guaranteed)
       */
      virtual Ptr<cs::Entry>
      End () = 0;

      /**
       * @brief Advance the iterator
       */
      virtual Ptr<cs::Entry>
      Next (Ptr<cs::Entry>) = 0;

      ////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////

      /**
       * @brief Static call to cheat python bindings
       */
      static inline Ptr<ContentStore>
      GetContentStore (Ptr<Object> node);

      typedef void (* CacheHitTracedCallback)
	  (const Ptr<const Interest>, const Ptr<const Data>);

      typedef void (* CacheMissTracedCallback)
     	  (const Ptr<const Interest>, const Ptr<const Data>);

    protected:
      TracedCallback<Ptr<const Interest>,
      Ptr<const Data> > m_cacheHitsTrace; ///< @brief trace of cache hits

      TracedCallback<Ptr<const Interest> > m_cacheMissesTrace; ///< @brief trace of cache misses
    };

    inline std::ostream&
    operator<< (std::ostream &os, const ContentStore &cs)
    {
      cs.Print (os);
      return os;
    }

    inline Ptr<ContentStore>
    ContentStore::GetContentStore (Ptr<Object> node)
    {
      return node->GetObject<ContentStore> ();
    }
  } // namespace nnn
} // namespace ns3

#endif // NNN_ICN_CONTENT_STORE_H
